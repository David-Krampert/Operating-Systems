//David Krampert 

#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <limits.h>
#include <semaphore.h>

pthread_t t1, t2, t3, t4, t5;

sem_t m;
sem_t barrier_1;
sem_t barrier_2;

int global_int = 0;
int num_pthreads = 0;


void* function(void* args){

    for(int i = 1; i <= 10; i++){

      for(int j = 0; j < INT_MAX*0.01; j++){
        //wait
      }

        sem_wait(&m);
        global_int++;

      	if (global_int == num_pthreads) {
      		sem_wait(&barrier_2);
          sem_post(&barrier_1);
      	}
        sem_post(&m);

        sem_wait(&barrier_1);
        sem_post(&barrier_1);

        printf("Task Thread ID: %d, Iteration Number: %d\n\n", (int)pthread_self()%5,i);

        sem_wait(&m);

	      global_int--;

      	if (global_int == 0) {
      		sem_wait(&barrier_1);
          sem_post(&barrier_2);
      	}

        sem_post(&m);
        sem_wait(&barrier_2);
        sem_post(&barrier_2);
    }
    return NULL;
}


int main() {
  
  sem_init(&m, 0, 1);
  sem_init(&barrier_1, 0, 0);
  sem_init(&barrier_2, 0, 1);

  num_pthreads = 5;
  global_int = 0;
    
  pthread_create(&t1, NULL, function, NULL);
	pthread_create(&t2, NULL, function, NULL);
	pthread_create(&t3, NULL, function, NULL);
	pthread_create(&t4, NULL, function, NULL);
	pthread_create(&t5, NULL, function, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
    
  return 0;
}
