// name: Kaustubha Eluri
// email: eluri.k@northeastern.edu

// Compile with:
//
// gcc -lpthread hw12.c -o hw12
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 100

// shared variable
int counter = 0;
// mutex to protect shared variable
pthread_mutex_t lock;

// thread to be executed - unspecified variable arguments
void* thread1 (void* vargp) {
  // lock mutex
  pthread_mutex_lock(&lock);
  // add 1 to counter
  counter = counter + 1;
  // unlock mutex
  pthread_mutex_unlock(&lock);
  return NULL;
}

void* thread2 (void* vargp) {
  // lock mutex
  pthread_mutex_lock(&lock);
  // add 5 to counter
  counter = counter + 5;
  // unlock mutex
  pthread_mutex_unlock(&lock);
  return NULL;
}

void* thread3 (void* vargp) {
  // lock mutex
  pthread_mutex_lock(&lock);
  // subtract 2 from counter
  counter = counter - 2;
  // unlock mutex
  pthread_mutex_unlock(&lock);
  return NULL;
}

void* thread4 (void* vargp) {
  // lock mutex
  pthread_mutex_lock(&lock);
  // subtract 10 from counter
  counter = counter - 10;
  // unlock mutex
  pthread_mutex_unlock(&lock);
  return NULL;
}

int main() {
  // initialize mutex
  if (pthread_mutex_init(&lock, NULL) != 0) {
    printf("Mutex init has failed\n");
    return 1;
  }

  // array to keep Pthread IDs of created threads
  pthread_t tid[NTHREADS*4];
  int i;

  for (int run = 0; run < 3; ++run) {
    counter = 0;  // reset counter for each run
    printf("Run %d: Counter starts at %d\n", run + 1, counter);

    // create and run the threads
    for (i = 0; i < NTHREADS; ++i){
      pthread_create(&(tid[i]), NULL, thread1, NULL);
      pthread_create(&(tid[NTHREADS + i]), NULL, thread2, NULL);
      pthread_create(&(tid[NTHREADS*2 + i]), NULL, thread3, NULL);
      pthread_create(&(tid[NTHREADS*3 + i]), NULL, thread4, NULL);
    }

    // wait until all threads are done
    for (i = 0; i < NTHREADS*4; ++i){
      pthread_join(tid[i], NULL);
    }

    printf("Run %d: Counter ends at %d\n", run + 1, counter);
  }

  // destroy mutex
  pthread_mutex_destroy(&lock);

  return 0;
}
