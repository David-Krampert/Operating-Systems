//David Krampert

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int count = 0;

typedef struct{
	int N;
	int pid;
	int roundPlaying[1];
	int arr[1];
}semaphore_t;

semaphore_t sem;


int pid_round(semaphore_t *semaphore,int round, int player){

	for(int i = 0; i < semaphore->N-1; i++){
		if(i != player){
			if(semaphore->roundPlaying[i] >= round){
				return 1;
			}
		}
	}
	return 0;
}


void init(semaphore_t *semaphore, int start){


	semaphore->N = start;


	for(semaphore->pid = 0; semaphore->pid < semaphore->N; semaphore->pid++){

		semaphore->roundPlaying[semaphore->pid] = -1;

	}

	for(int round = 0; round < (semaphore->N); round++){
		semaphore->arr[round] = -1;

	}

}


void wait(semaphore_t *semaphore, int player){

	for(int round = 0; round < semaphore->N-1; round++){

		semaphore->roundPlaying[player] = round;
		semaphore->arr[round] = player;

		while(semaphore->arr[round] == player && pid_round(semaphore,round,player)){}
    
	}
}

void signal(semaphore_t *semaphore,int player){

	printf("No longer playing in the tournament, pthread %d releasing semaphore\n\n", player);
	semaphore->roundPlaying[player] = -1;

}

void *start_here(void *arg){

	int id = *((int *)arg);

	wait(&sem,id);


	for(int i = 0; i < 10; i++){
		count++;
		printf("Thread: %d \nGlobal: %d\n\n", id, count);
	}

	signal(&sem,id);
	return NULL;

}

int main(void) {

	init(&sem, 10);

	pthread_t tid[10];

	int tids[10];
	for(int i = 0; i < 10; i++){
		tids[i] = i;
	}

	for(int i = 0; i<10; i++){
		pthread_create(&tid[i], NULL, start_here, &tids[i]);
	}

	for(int i = 0; i<10; i++){
		pthread_join(tid[i], NULL);
	}

	printf("\n\n\nFinal Global: %d\n\n\n", count);

	return 0;
}