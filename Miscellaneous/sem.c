#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

  sem_t s; /* semaphore s */
  void *foo(void *vargp) {
      int myid;
      myid = *((int *)vargp);
      sem_post(&s);
      printf("Thread %d\n", myid);
}
  int main() {
      pthread_t tid[2];
      int i;
      sem_open("sem1", 0, 0); /* S=0 INITIALLY */
      for (i = 0; i < 2; i++) {
          pthread_create(&tid[i], 0, foo, &i);
          sem_wait(&s);
      }
      pthread_join(tid[0], 0);
      pthread_join(tid[1], 0);
      sem_close(&s);
}