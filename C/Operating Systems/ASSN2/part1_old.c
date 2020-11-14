#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS	5

int CurrentID = 1;
pthread_mutex_t mutex_lock;

void *increment_id(void *threadid)
{
  long tid;
  tid = (long)threadid + 1;
  int myturn_counter = 0;
  int notmyturn_counter = 0;
  while (myturn_counter < 10) {
    pthread_mutex_lock(&mutex_lock);
    if (CurrentID == tid) {
      myturn_counter++;
      CurrentID++;
      if (CurrentID == 6)
        CurrentID = 1;
      printf("Thread #%ld: My turn (#%d)! CurrentID is now %d\n", tid, myturn_counter, CurrentID);
    }
    else {
      notmyturn_counter++;
      printf("Thread #%ld: Not My Turn (#%d)! CurrentID is %d\n", tid, notmyturn_counter, CurrentID);
    }
    pthread_mutex_unlock(&mutex_lock);
  }
  pthread_exit(NULL);
}

int main(void)
{
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;
  pthread_mutex_init(&mutex_lock, NULL);
  for(t = 0; t < NUM_THREADS; t++){
    printf("In main: creating thread %ld\n", t+1);
    rc = pthread_create(&threads[t], NULL, increment_id, (void*)t);
    if (rc){
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
      }
    }

   /* Last thing that main() should do */
  pthread_mutex_destroy(&mutex_lock);
  pthread_exit(NULL);
}