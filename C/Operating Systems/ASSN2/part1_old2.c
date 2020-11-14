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
  pthread_mutex_lock(&mutex_lock);
  if (CurrentID == tid) {
    CurrentID++;
    if (CurrentID == 6)
      CurrentID = 1;
    printf("Thread #%ld: My turn! CurrentID is now %d\n", tid, CurrentID);
  }
  else {
    printf("Thread #%ld: Not My Turn! CurrentID is %d\n", tid, CurrentID);
  }
  pthread_mutex_unlock(&mutex_lock);
  pthread_exit(NULL);
}

int main(void)
{
  pthread_t threads[NUM_THREADS];
  pthread_mutex_init(&mutex_lock, NULL);
  int rc;
  long t;
  for(t = 0; t < NUM_THREADS; t++) {
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