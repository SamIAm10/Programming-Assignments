#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS	5
#define BUFFER_SIZE 5

pthread_mutex_t mutex_lock;
int buffer[BUFFER_SIZE];
int next_produced = 0, next_consumed = 0;
int in = 0, out = 0;
int num_produced = 0, num_consumed = 0;
int full = 0, empty = 0;

void *producer(void *threadid)
{
    long tid;
    tid = (long)threadid;
    while (1) {
        next_produced++;
        pthread_mutex_lock(&mutex_lock);
        if (((in + 1) % BUFFER_SIZE) == out) {
            full++;
            while (((in + 1) % BUFFER_SIZE) == out);
        }
        buffer[in] = next_produced;
        num_produced++;
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex_lock);
    }
    pthread_exit(NULL);
}

void *consumer(void *threadid)
{
    long tid;
    tid = (long)threadid;
    while (1) {
        pthread_mutex_lock(&mutex_lock);
        if (in == out) {
            empty++;
            while(in == out);
        }
        next_consumed = buffer[out];
        num_consumed++;
        // termination of program condition
        if (num_consumed >= 200) {
            pthread_mutex_destroy(&mutex_lock);
            printf("Full: %d\n", full);
            printf("Empty: %d\n", empty);
            exit(0);
        }
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex_lock);
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex_lock, NULL);
    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1;
    }

    pthread_create(&threads[0], NULL, producer, (void*)0);
    pthread_create(&threads[1], NULL, consumer, (void*)1);
    pthread_create(&threads[2], NULL, producer, (void*)2);
    pthread_create(&threads[3], NULL, consumer, (void*)3);
    pthread_create(&threads[4], NULL, consumer, (void*)4);

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex_lock);
    pthread_exit(NULL);
}