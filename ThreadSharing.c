#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <semaphore.h>
#include <limits.h>


pthread_t t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;

sem_t x;
sem_t b1;
sem_t b2;

int global = 0;
int pthread_cnt = 0;


void* helperFun(void* args){

  for(int i = 0; i <= 10; i++){

    sem_wait(&x);
    global++;

    if (global == pthread_cnt){
    	sem_wait(&b2);
      sem_post(&b1);
    }
    sem_post(&x);
    sem_wait(&b1);
    sem_post(&b1);

    printf("pThread ID: %d, Global Int: %d\n\n", (int)pthread_self()%5,i);

    sem_wait(&x);
    global--;

    if (global == 0) {
      sem_wait(&b1);
      sem_post(&b2);
    }

    sem_post(&x);
    sem_wait(&b2);
    sem_post(&b2);
  }
  return NULL;
}


int main() {
  
  sem_init(&x, 0, 1);
  sem_init(&b1, 0, 0);
  sem_init(&b2, 0, 1);

  pthread_cnt = 10;
    
  //cerate the pthreads
  pthread_create(&t1, NULL, helperFun, NULL);
	pthread_create(&t2, NULL, helperFun, NULL);
	pthread_create(&t3, NULL, helperFun, NULL);
	pthread_create(&t4, NULL, helperFun, NULL);
	pthread_create(&t5, NULL, helperFun, NULL);
  pthread_create(&t6, NULL, helperFun, NULL);
  pthread_create(&t7, NULL, helperFun, NULL);
  pthread_create(&t8, NULL, helperFun, NULL);
  pthread_create(&t9, NULL, helperFun, NULL);
  pthread_create(&t10, NULL, helperFun, NULL);

  //join pthreads 
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
  pthread_join(t6, NULL);
	pthread_join(t7, NULL);
	pthread_join(t8, NULL);
	pthread_join(t9, NULL);
	pthread_join(t10, NULL);
  
  printf("The final Global Int: %d\n\n", global);
 
  return 0;
}
/*From running a few time and seeing the output I can say that the thread ID is
random and incrementing the global int doesn't affect the final results. 
I'm having trouble getting the final Global Int to read 100 with the way I wrote this code.
*/

