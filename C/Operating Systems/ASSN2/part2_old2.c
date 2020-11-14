#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS	5
#define BUFFER_SIZE 5

pthread_mutex_t mutex_lock, full, empty;
int buffer[BUFFER_SIZE];
int next_produced = 0, next_consumed = 0;
int in = 0, out = 0;
int num_produced = 0, num_consumed = 0;
int full_count = 0, empty_count = 0;
int is_full = 0, is_empty = 0;

void *producer(void *threadid)
{
    long tid;
    tid = (long)threadid;
    while (1) {
        next_produced++;
        pthread_mutex_lock(&empty);
        pthread_mutex_lock(&mutex_lock);
        /*int i;
        int is_not_full = 0;
        for (i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] == -1)
                is_not_full = 1;
                full_count++;
        }*/
        if (buffer[in] != -1) {
            pthread_mutex_unlock(&mutex_lock);
            pthread_mutex_unlock(&full);
            full_count++;
            continue;
        }
        buffer[in] = next_produced;
        num_produced++;
        printf("Producer #%ld: Put %d in slot %d\n", tid, next_produced, in);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex_lock);
        pthread_mutex_unlock(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *threadid)
{
    long tid;
    tid = (long)threadid;
    while (1) {
        pthread_mutex_lock(&full);
        pthread_mutex_lock(&mutex_lock);
        if (buffer[out] == -1) {
            pthread_mutex_unlock(&mutex_lock);
            pthread_mutex_unlock(&empty);
            empty_count++;
            continue;
        }
        next_consumed = buffer[out];
        printf("Consumer #%ld: Took %d from slot %d\n", tid, next_consumed, out);
        num_consumed++;
        // termination of program condition
        if (num_consumed >= 199) {
            pthread_mutex_destroy(&mutex_lock);
            pthread_mutex_destroy(&full);
            pthread_mutex_destroy(&empty);
            printf("Full: %d\n", full_count);
            printf("Empty: %d\n", empty_count);
            exit(0);
        }
        buffer[out] = -1;
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex_lock);
        pthread_mutex_unlock(&empty);
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex_lock, NULL);
    pthread_mutex_init(&full, NULL);
    pthread_mutex_init(&empty, NULL);

    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1;
    }

    printf("Creating producer #%d\n", 0);
    pthread_create(&threads[0], NULL, producer, (void*)0);
    printf("Creating consumer #%d\n", 1);
    pthread_create(&threads[1], NULL, consumer, (void*)1);
    printf("Creating producer #%d\n", 2);
    pthread_create(&threads[2], NULL, producer, (void*)2);
    printf("Creating consumer #%d\n", 3);
    pthread_create(&threads[3], NULL, consumer, (void*)3);
    printf("Creating consumer #%d\n", 4);
    pthread_create(&threads[4], NULL, consumer, (void*)4);

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex_lock);
    pthread_exit(NULL);
}