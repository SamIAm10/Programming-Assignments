#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS	5 // total number of threads

int CurrentID = 1; // shared variable between threads
pthread_mutex_t mutex_lock; // mutex lock
int myturn_counter[NUM_THREADS]; // counter for "my turn" statements
int notmyturn_counter[NUM_THREADS]; // counter for "not my turn" statements

void *increment_id(void *threadid)
{
    long tid;
    tid = (long)threadid + 1; // add one to thread id 
    pthread_mutex_lock(&mutex_lock); // lock mutex
    if (CurrentID == tid) { // if id's match
        myturn_counter[tid-1]++; // increment "my turn" counter for this thread
        CurrentID++;
        if (CurrentID == 6)
            CurrentID = 1;
        printf("Thread #%ld: My turn (#%d)! CurrentID is now %d\n", tid, myturn_counter[tid-1], CurrentID);
		/* termination condition */
        if (myturn_counter[tid-1] >= 10 && tid == 5) {
            pthread_mutex_destroy(&mutex_lock); // destroy mutex
			exit(0); // terminate program
        }
    }
    else {
        notmyturn_counter[tid-1]++; // increment "not my turn" counter for this thread
        printf("Thread #%ld: Not My Turn (#%d)! CurrentID is %d\n", tid, notmyturn_counter[tid-1], CurrentID);
    }
    pthread_mutex_unlock(&mutex_lock); // release mutex
    pthread_exit(NULL); // exit thread
}

int main(void)
{
    pthread_t threads[NUM_THREADS]; // initialize threads
    pthread_mutex_init(&mutex_lock, NULL); // initialize mutex
    
    long t;
    while (1) { // create threads until termination condition is reached
        for (t = 0; t < NUM_THREADS; t++) {
            pthread_create(&threads[t], NULL, increment_id, (void*)t);
        }
    }
    
    pthread_mutex_destroy(&mutex_lock);
    pthread_exit(NULL);
}