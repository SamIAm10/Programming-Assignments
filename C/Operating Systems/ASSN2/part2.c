#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS	5 // total number of threads
#define BUFFER_SIZE 5 // size of buffer (CHANGE THIS TO 5, 10, OR 25)

pthread_mutex_t mutex_lock; // mutex lock
int buffer[BUFFER_SIZE]; // shared buffer between producers and consumers
int next_produced = 0, next_consumed = 0; // variables for storing produced/consumed items
int in = 0, out = 0; // indexes of produced/consumed item
int num_produced = 0, num_consumed = 0; // counters for number of produced/consumed items
int full_count = 0, empty_count = 0; // counters for number of times producers/consumers go to sleep

void *producer(void *threadid)
{
    long tid;
    tid = (long)threadid;
    while (1) {
        pthread_mutex_lock(&mutex_lock); // lock mutex
        // check if the queue is full or not
        int i;
        int is_not_full = 0;
        for (i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] == -1) {
                is_not_full = 1;
            }
        }
        // if it is, release mutex and iterate
        if (is_not_full == 0) {
            pthread_mutex_unlock(&mutex_lock);
            full_count++;
        }
        // if not, put new integer in queue
        else {
            next_produced++;
            buffer[in] = next_produced; // put integer in slot
            num_produced++;
            //printf("Producer #%ld: Put %d in slot %d\n", tid, next_produced, in);
            in = (in + 1) % BUFFER_SIZE;
            pthread_mutex_unlock(&mutex_lock); // release mutex
        }
    }
    pthread_exit(NULL);
}

void *consumer(void *threadid)
{
    long tid;
    tid = (long)threadid;
    while (1) {
        pthread_mutex_lock(&mutex_lock); // lock mutex
        // check if the queue is empty or not
        int i;
        int is_not_empty = 0;
        for (i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] != -1) {
                is_not_empty = 1;
            }
        }
        // if it is, release mutex and iterate
        if (is_not_empty == 0) {
            pthread_mutex_unlock(&mutex_lock);
            empty_count++;
        }
        // if not, take an integer from queue
        else {
            next_consumed = buffer[out]; // take integer from slot
            //printf("Consumer #%ld: Took %d from slot %d\n", tid, next_consumed, out);
            num_consumed++;
            /* termination condition */
            if (num_consumed >= 200) {
                pthread_mutex_destroy(&mutex_lock); // destroy mutex
                printf("\nThe producer went to sleep %d times due to full queue\n", full_count);
                printf("The consumer went to sleep %d times due to empty queue\n", empty_count);
                exit(0); // terminate program
            }
            buffer[out] = -1; // set slot to empty once integer is taken out
            out = (out + 1) % BUFFER_SIZE;
            pthread_mutex_unlock(&mutex_lock); // release mutex
        }
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t threads[NUM_THREADS]; // initialize threads 
    pthread_mutex_init(&mutex_lock, NULL); // initialize mutex

    // set all elements in queue to -1 initially (-1 = an empty slot)
    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1;
    }

    // create producer and consumer threads
    printf("Creating producer, ID = #%d\n", 0);
    pthread_create(&threads[0], NULL, producer, (void*)0);
    printf("Creating consumer, ID = #%d\n", 1);
    pthread_create(&threads[1], NULL, consumer, (void*)1);
    printf("Creating producer, ID = #%d\n", 2);
    pthread_create(&threads[2], NULL, producer, (void*)2);
    printf("Creating consumer, ID = #%d\n", 3);
    pthread_create(&threads[3], NULL, consumer, (void*)3);
    printf("Creating consumer, ID = #%d\n", 4);
    pthread_create(&threads[4], NULL, consumer, (void*)4);

    // join threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex_lock);
    pthread_exit(NULL);
}