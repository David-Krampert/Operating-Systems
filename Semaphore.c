//David Krampert CS537 HW8
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>

int x = 0;
sem_t semaphore;

void* func(void * id)
{
  sem_wait(&semaphore);
  
  int* theId = (int*)id;

  //while(!start);
 
  for(int i = 0; i < 10; i++)
  {
    x++;
    printf("Thread %d increments x to %d\n", *theId, x);
  }
  sem_post(&semaphore);
  return NULL;
}

int main()
{
  sem_init(&semaphore,0,1);
  pthread_t tid[10];
  int tid2[10];
  int error;
  for(int i = 0; i < 10; i++)
  {
    tid2[i] = i;
    if(error = pthread_create(&tid[i], NULL, func, &tid2[i]))
    {
      printf("Failed to create thread: %s\n", strerror(error));
      exit(-1);
    }
  }

  //start = true;

  for(int i = 0; i < 10; i++)
  {
    if(error = pthread_join(tid[i],NULL))
    {
      fprintf(stderr, "Failed to join thread: %s\n", strerror(error));
      exit(-1);
    }
  }
  printf("Final value of x: %d\n", x);
  return 0;
}