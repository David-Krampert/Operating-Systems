#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <semaphore.h>

sigset_t mask;

int MAX_TIME = 30;
int MIN_TIME = 1;

int SNITCH_WAIT = 2;
int BLUDGER_WAIT = 15;
int QUAFFLE_WAIT = 2;

int SEEKER_WAIT = 25;
int KEEPER_WAIT = 5;
int BEATER_WAIT = 2;
int CHASER_WAIT = 2;


sem_t semaphore;
struct sigaction BLUDGER;
struct sigaction USER_1;
struct sigaction USER_2;

pthread_t Team1_Seeker,
TEAM_1_KEEPER,
TEAM_1_CHASER1,
TEAM_1_CHASER2,
TEAM_1_CHASER3,
TEAM_1_BEATER1,
TEAM_1_BEATER2,

TEAM_2_SEEKER, 
TEAM_2_KEEPER,
TEAM_2_CHASER1,
TEAM_2_CHASER2,
TEAM_2_CHASER3,
TEAM_2_BEATER1,
TEAM_2_BEATER2,

QUAFFEL,
BLUDGER_1,
BLUDGER_2,
SNITCH,

GOAL_1,
GOAL_2;

int SCORE_1 = 0;
int SCORE_2 = 0;

pthread_t *players[14] = {
&Team1_Seeker, 
&TEAM_1_KEEPER,
&TEAM_1_CHASER1,
&TEAM_1_CHASER2, 
&TEAM_1_CHASER3,
&TEAM_1_BEATER1,
&TEAM_1_BEATER2,
&TEAM_2_SEEKER, 
&TEAM_2_KEEPER,
&TEAM_2_CHASER1,
&TEAM_2_CHASER2,
&TEAM_2_CHASER3,
&TEAM_2_BEATER1,
&TEAM_2_BEATER2
};

int TEAM_1_SCORE = 0, TEAM_2_SCORE = 0, s_catch = 0;

int STILL_PLAYING[14];
int OUT[14];

int remain1 = 7, remain2 = 7;

void sleeper(int temp){
  sleep(temp);
}

int determine_team(pthread_t p){

  if(pthread_equal(p,Team1_Seeker) || pthread_equal(p,TEAM_1_KEEPER) ||pthread_equal(p,TEAM_1_BEATER1) ||pthread_equal(p,TEAM_1_BEATER2) ||pthread_equal(p,TEAM_1_CHASER1) ||pthread_equal(p,TEAM_1_CHASER2) ||pthread_equal(p,TEAM_1_CHASER3)){
    return 1;

  }else if(pthread_equal(p,TEAM_2_SEEKER) || pthread_equal(p,TEAM_2_KEEPER) ||pthread_equal(p,TEAM_2_BEATER1) ||pthread_equal(p,TEAM_2_BEATER2) ||pthread_equal(p,TEAM_2_CHASER1) ||pthread_equal(p,TEAM_2_CHASER2) ||pthread_equal(p,TEAM_2_CHASER3)){

  return 2;

  }

  else{
    return 0;
  }
}

char* determine_player_name(pthread_t p){

  if(pthread_equal(p, *players[0])){
    return "Seeker from Team 1";
  }
  else if(pthread_equal(p, *players[1])){
    return "Keeper from Team 1";
  }
  else if(pthread_equal(p, *players[2])){
    return "Beater 1 from Team 1";
  }
  else if(pthread_equal(p, *players[3])){
    return "Beater 2 from Team 1";
  }
  else if(pthread_equal(p, *players[4])){
    return "Chaser 1 from Team 1";
  }
  else if(pthread_equal(p, *players[5])){
    return "Chaser 2 from Team 1";
  }
  else if(pthread_equal(p, *players[6])){
    return "Chaser 3 from Team 1";
  }
  else if(pthread_equal(p, *players[7])){
    return "Seeker from Team 2";
  }
  else if(pthread_equal(p, *players[8])){
    return "Keeper from Team 2";
  }
  else if(pthread_equal(p, *players[9])){
    return "Beater 1 from Team 2";
  }
  else if(pthread_equal(p, *players[10])){
    return "Beater 2 from Team 2";
  }
  else if(pthread_equal(p, *players[11])){
    return "Chaser 1 from Team 2";
  }
  else if(pthread_equal(p, *players[12])){
    return "Chaser 2 from Team 2";
  }
  else if(pthread_equal(p, *players[13])){
    return "Chaser 3 from Team 2";
  }

 
  return "";
}

void* Bludger(void *ptr){

  pthread_detach(pthread_self());

  while(1){

    int wait = (rand()%BLUDGER_WAIT)+2;
    sleep(wait);

    sem_wait(&semaphore);

    srand(time(NULL));
    int player_picked = rand() % 14;
    
    if(player_picked == 0){
			if(OUT[0] == 0){
			pthread_kill(Team1_Seeker, SIGINT);
			}
		}
		else if(player_picked == 1){
			
			if(OUT[1] == 0){
			pthread_kill(TEAM_1_KEEPER, SIGINT);
			}
		}
		else if(player_picked == 2){
			
			if(OUT[2] == 0){
			pthread_kill(TEAM_1_CHASER1, SIGINT);
			}
		}
		else if(player_picked == 3){
			
			if(OUT[3] == 0){
			pthread_kill(TEAM_1_CHASER2, SIGINT);
			}
		}
		else if(player_picked == 4){
			
			if(OUT[4] == 0){
			pthread_kill(TEAM_1_CHASER3, SIGINT);
			}
		}
		else if(player_picked == 5){
		
			if(OUT[5] == 0){
			pthread_kill(TEAM_1_BEATER1, SIGINT);
			}
		}
		else if(player_picked == 6){
			
			if(OUT[6] == 0){
			pthread_kill(TEAM_1_BEATER2, SIGINT);
			}
		}
		else if(player_picked == 7){
			if(OUT[7] == 0){
			pthread_kill(TEAM_2_SEEKER, SIGINT);
			}
		}
		else if(player_picked == 8){
			
			if(OUT[8] == 0){
			pthread_kill(TEAM_2_KEEPER, SIGINT);
			}
		}
		else if(player_picked == 9){
			
			if(OUT[9] == 0){
			pthread_kill(TEAM_2_CHASER1, SIGINT);
			}
		}
		else if(player_picked == 10){
			
			if(OUT[10] == 0){
			pthread_kill(TEAM_2_CHASER2, SIGINT);
			}
		}
		else if(player_picked == 11){
			
			if(OUT[11] == 0){
			pthread_kill(TEAM_2_CHASER3, SIGINT);
			}
		}
		else if(player_picked == 12){
			
			if(OUT[12] == 0){
			pthread_kill(TEAM_2_BEATER1, SIGINT);
			}
		}
		else if(player_picked == 13){
			
			if(OUT[13] == 0){
			pthread_kill(TEAM_2_BEATER2, SIGINT);
			}
		}

    sem_post(&semaphore); 
  }

}




void *Snitch(void *ptr){

    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    pthread_detach(pthread_self());   
  
    while(1){                         

    sleeper((rand()%SNITCH_WAIT));  

	  sem_wait(&semaphore);                 

    if(s_catch == 0)
      s_catch = 1;                     
    else
      s_catch = 0;                      

	  sem_post(&semaphore);                 
  }
}

void *Quaffle(void * arg){

  sigfillset(&mask);
  sigprocmask(SIG_SETMASK, &mask, NULL);

	pthread_detach(pthread_self());

	while(1){

		sleep((rand() % QUAFFLE_WAIT)+QUAFFLE_WAIT);

    sem_wait(&semaphore);                 

		int player = rand() % 6;
		if(player == 0){
			if(OUT[2] == 0){
			pthread_kill(TEAM_1_CHASER1, SIGUSR2);
			}
		}
		else if(player == 1){
			if(OUT[3] == 0){
			pthread_kill(TEAM_1_CHASER2, SIGUSR2);
			}
		}
		else if(player == 2){
			if(OUT[4] == 0){
			pthread_kill(TEAM_1_CHASER3, SIGUSR2);
			}
		}
		else if(player == 3){
			if(OUT[9] == 0){
			pthread_kill(TEAM_2_CHASER1, SIGUSR2);
			}
		}
		else if(player == 4){
			if(OUT[10] == 0){
			pthread_kill(TEAM_2_CHASER2, SIGUSR2);
			}
		}
		else{
			if(OUT[11] == 0){
			pthread_kill(TEAM_2_CHASER3, SIGUSR2);
			}
		}
    sem_post(&semaphore);                 
	}	
}


void *Seeker1(void *ptr){
  
  sigfillset(&mask);
  sigprocmask(SIG_SETMASK, &mask, NULL);

  pthread_detach(pthread_self());   

  while(1){                         
    sleep(rand()%SEEKER_WAIT);    
    sem_wait(&semaphore);                               

    printf("\nThe golden Snitch is on the filed...\n"); 



    if(s_catch == 1){                               

      if(pthread_equal(pthread_self(), Team1_Seeker) && OUT[0] == 0){  
        TEAM_1_SCORE += 150;
      }

      if(pthread_equal(pthread_self(), Team1_Seeker) && OUT[0] == 0){  
        printf("\nThe Seeker of Team 1 has caught the Snitch\n");
        printf("Game Over. Final score: Team 1: %i, Team 2: %i\n", TEAM_1_SCORE, TEAM_2_SCORE);
        exit(0);                     
      }
    }
    sem_post(&semaphore);                
  }
}


void *Seeker2(void *ptr){

  sigfillset(&mask);
  sigprocmask(SIG_SETMASK, &mask, NULL); 

  pthread_detach(pthread_self());   

  while(1){                         
    sleep(rand()%SEEKER_WAIT);    
    sem_wait(&semaphore);                               

    printf("\nThe golden Snitch is on the field...\n"); 



    if(s_catch == 1){                              

      if(pthread_equal(pthread_self(), TEAM_2_SEEKER) && OUT[7] == 0){  
        TEAM_2_SCORE += 150;
      }

      if(pthread_equal(pthread_self(), TEAM_2_SEEKER) && OUT[7] == 0){  
        printf("\nThe Seeker of Team 2 has caught the Snitch\n");
        printf("Game Over. Final score: Team 1: %i, Team 2: %i\n", TEAM_1_SCORE, TEAM_2_SCORE);
        exit(0);                      
      }
    }
    sem_post(&semaphore);                 
  }
}


void *goals(void *ptr) 
{
    pthread_detach(pthread_self());
    while(1){
      pause();
    }
}

void *Keeper(void *ptr)
{

  sigfillset(&mask);
  sigprocmask(SIG_SETMASK, &mask, NULL);

  pthread_detach(pthread_self());

while(1){
  sleep(rand() % KEEPER_WAIT);

  if(pthread_self() == TEAM_1_KEEPER){
    if(OUT[1] == 0){
      pthread_kill(GOAL_1,SIGUSR1);
    }
  }else if(pthread_self() == TEAM_2_KEEPER){
    if(OUT[8] == 0){
      pthread_kill(GOAL_2,SIGUSR1);
    }
  }
}
}

void *Chaser(void *ptr) 
{
    pthread_detach(pthread_self());
    while(1){
      pause();
    }
}

void *Beater(void *p){

  sigfillset(&mask);
  sigprocmask(SIG_SETMASK, &mask, NULL);

  pthread_detach(pthread_self());

  while(1){
    
    sleep((rand()%BEATER_WAIT)+BEATER_WAIT);

    sem_wait(&semaphore);

    int team_number = determine_team(pthread_self());
    int i = 0;
        
    if(team_number == 1){

      i = rand()%7;

      while(OUT[i] != 0){
        i = rand()%7;
      }
    }
    else{

      i = (rand()%7)+7;

      while(OUT[i] != 0){
        i = (rand()%7)+7;
      }
    }

    pthread_t *temp = players[i];
    pthread_kill(*temp, SIGUSR1);  
    
    sem_post(&semaphore);
  }
}


void SIGINT_helper(int integer){


    if(pthread_self() == Team1_Seeker){
      printf("The Beater is trying to hit Seeker from Team 1 with a flying Bludger\n");
      STILL_PLAYING[0] = 1;
      sleep(2);

      if(STILL_PLAYING[0] == 1){
        printf("Seeker from team 1 was hit and is no longer in the game.\n");
        OUT[0] = 1;
        remain1--;
      }else{
        printf("Seeker from team 1 was saved by a Beater from a flying Bludger!\n");
      }
    }


    else if(pthread_self() == TEAM_1_KEEPER){
      printf("The Beater is trying to hit Keeper from Team 1 with a flying Bludger\n");
      STILL_PLAYING[1] = 1;
      sleep(2);

      if(STILL_PLAYING[1] == 1){
        printf("Keeper from team 1 was hit and is no longer in the game.\n");
        OUT[1] = 1;
        remain1--;
      }else{
        printf("Keeper from team 1 was saved by a Beater from a flying Bludger!\n");
      }
    }


    else if(pthread_self() == TEAM_1_CHASER1){
      printf("The Beater is trying to hit Chaser1 from Team 1 with a flying Bludger\n");
      STILL_PLAYING[2] = 1;
      sleep(2);

      if(STILL_PLAYING[2] == 1){
        printf("Chaser1 from team 1 was hit and is no longer in the game.\n");
        OUT[2] = 1;
        remain1--;
      }else{
        printf("Chaser1 from team 1 was saved by a Beater from a flying Bludger!\n");
      }
    }


    else if(pthread_self() == TEAM_1_CHASER2){
      printf("The Beater is trying to hit Chaser2 from Team 1 with a flying Bludger\n");
      STILL_PLAYING[3] = 1;
      sleep(2);

      if(STILL_PLAYING[3] == 1){
        printf("Chaser2 from team 1 was hit and is no longer in the game.\n");
        OUT[3] = 1;
        remain1--;
      }else{
        printf("Chaser2 from team 1 was saved by a Beater from a flying Bludger!\n");
      }
    }


    else if(pthread_self() == TEAM_1_CHASER3){
      printf("The Beater is trying to hit Chaser3 from Team 1 with a flying Bludger\n");
      STILL_PLAYING[4] = 1;
      sleep(2);

      if(STILL_PLAYING[4] == 1){
        printf("Chaser3 from team 1 was hit and is no longer in the game.\n");
        OUT[4] = 1;
        remain1--;
      }else{
        printf("Chaser3 from team 1 was saved by a Beater from a flying Bludger!\n");
      }
    }


    else if(pthread_self() == TEAM_1_BEATER1){
      printf("The Beater is trying to hit Beater1 from Team 1 with a flying Bludger\n");
      STILL_PLAYING[5] = 1;
      sleep(2);

      if(STILL_PLAYING[5] == 1){
        printf("Beater1 from team 1 was hit and is no longer in the game.\n");
        OUT[5] = 1;
        remain1--;
      }else{
        printf("Beater1 from team 1 was saved by a Beater from a flying Bludger!\n");
      }
    }

    else if(pthread_self() == TEAM_1_BEATER2){
      printf("The Beater is trying to hit Beater2 from Team 1 with a flying Bludger\n");
      STILL_PLAYING[6] = 1;
      sleep(2);

      if(STILL_PLAYING[6] == 1){
        printf("Beater2 from team 1 was hit and is no longer in the game.\n");
        OUT[6] = 1;
        remain1--;
      }else{
        printf("Beater2 from team 1 was saved by a Beater from a flying Bludger!\n");
      }
    }

    else if(pthread_self() == TEAM_2_SEEKER){
      printf("The Beater is trying to hit Seeker from Team 2 with a flying Bludger\n");
      STILL_PLAYING[7] = 1;
      sleep(2);

      if(STILL_PLAYING[7] == 1){
        printf("Seeker from team 2 was hit and is no longer in the game.\n");
        OUT[7] = 1;
        remain2--;
      }else{
        printf("Seeker from team 2 was saved by a Beater from a flying Bludger!\n");
      }
    }


    else if(pthread_self() == TEAM_2_KEEPER){
      printf("The Beater is trying to hit Keeper from Team 2 with a flying Bludger\n");
      STILL_PLAYING[8] = 1;
      sleep(2);

      if(STILL_PLAYING[8] == 1){
        printf("Keeper from team 2 was hit and is no longer in the game.\n");
        OUT[8] = 1;
        remain2--;
      }else{
        printf("Keeper from team 2 was saved by a Beater from a flying Bludger!\n");
      }
    }


    else if(pthread_self() == TEAM_2_CHASER1){
      printf("The Beater is trying to hit Chaser1 from Team 2 with a flying Bludger\n");
      STILL_PLAYING[9] = 1;
      sleep(2);

      if(STILL_PLAYING[9] == 1){
        printf("Chaser1 from team 2 was hit and is no longer in the game.\n");
        OUT[9] = 1;
        remain2--;
      }else{
        printf("Chaser1 from team 2 was saved by a Beater from a flying Bludger!\n");
      }
    }


    else if(pthread_self() == TEAM_2_CHASER2){
      printf("The Beater is trying to hit Chaser2 from Team 2 with a flying Bludger\n");
      STILL_PLAYING[10] = 1;
      sleep(2);

      if(STILL_PLAYING[10] == 1){
        printf("Chaser2 from team 2 was hit and is no longer in the game.\n");
        OUT[10] = 1;
        remain2--;
      }else{
        printf("Chaser2 from team 2 was saved by a Beater from a flying Bludger!\n");
      }
    }


    else if(pthread_self() == TEAM_2_CHASER3){
      printf("The Beater is trying to hit Chaser3 from Team 2 with a flying Bludger\n");
      STILL_PLAYING[11] = 1;
      sleep(2);

      if(STILL_PLAYING[11] == 1){
        printf("Chaser3 from team 2 was hit and is no longer in the game.\n");
        OUT[11] = 1;
        remain2--;
      }else{
        printf("Chaser3 from team 2 was saved by a Beater from a flying Bludger!\n");
      }
    }


    else if(pthread_self() == TEAM_2_BEATER1){
      printf("The Beater is trying to hit Beater1 from Team 2 with a flying Bludger\n");
      STILL_PLAYING[12] = 1;
      sleep(2);

      if(STILL_PLAYING[12] == 1){
        printf("Beater1 from team 2 was hit and is no longer in the game.\n");
        OUT[12] = 1;
        remain2--;
      }else{
        printf("Beater1 from team 2 was saved by a Beater with a flying Bludger!\n");
      }
    }

    else if(pthread_self() == TEAM_2_BEATER2){
      printf("The Beater is trying to hit Beater2 from Team 2 with a flying Bludger\n");
      STILL_PLAYING[13] = 1;
      sleep(2);

      if(STILL_PLAYING[13] == 1){
        printf("Beater2 from team 2 was hit and is no longer in the game.\n");
        OUT[13] = 1;
        remain2--;
      }else{
        printf("Beater2 from team 2 was saved by a Beater from a flying Bludger!\n");
      }
    }
  

    if(pthread_self() == GOAL_1){
      SCORE_1 = 0;
      sleep(2);

      if(SCORE_1 == 0){
        printf("Team 2 has scored!\n");
        TEAM_2_SCORE += 10;
        printf("Team 1 Score: %d\n", TEAM_1_SCORE);
        printf("Team 2 Score: %d\n", TEAM_2_SCORE);
      }
      else{
        printf("Keeper from Team 1 has blocked the shot on goal\n");
      }
    }
    else if(pthread_self() == GOAL_2){
      SCORE_2 = 0;
      sleep(2);

      if(SCORE_2 == 0){
        printf("Team1 has scored!\n");
        TEAM_1_SCORE += 10;
        printf("Team1 Score: %d\n", TEAM_1_SCORE);
        printf("Team2 Score: %d\n", TEAM_2_SCORE);
      }
      else{
        printf("Keeper from Team 2 has blocked the shot on goal\n");
      }
    }

    if(remain1 <= 0){
      printf("Team 2 Wins because all Players from Team 1 have fallen off their brooms\n");
      printf("Team 1 Score: %d", TEAM_1_SCORE);
      printf("Team 2 Score: %d", TEAM_2_SCORE);
      exit(0);
    }
    else if(remain2 <= 0){
      printf("\n\nTeam 1 Wins because all Players from Team 2 have fallen off their brooms\n");
      printf("Team 1 Score: %d\n", TEAM_1_SCORE);
      printf("Team 2 Score: %d\n", TEAM_2_SCORE);
      exit(0);
  }
}

void SIGUSR1_helper(int num){

  if(pthread_self() == Team1_Seeker){
		STILL_PLAYING[0] = 0;
	}
	else if(pthread_self() == TEAM_1_KEEPER){
		STILL_PLAYING[1] = 0;
	}
	else if(pthread_self() == TEAM_1_CHASER1){
		STILL_PLAYING[2] = 1;
	}
	else if(pthread_self() == TEAM_1_CHASER2){
		STILL_PLAYING[3] = 1;
	}
	else if(pthread_self() == TEAM_1_CHASER3){
		STILL_PLAYING[4] = 1;
	}
	else if(pthread_self() == TEAM_1_BEATER1){
		STILL_PLAYING[5] = 1;
	}
	else if(pthread_self() == TEAM_1_BEATER2){
		STILL_PLAYING[6] = 1;
	}
	else if(pthread_self() == TEAM_2_SEEKER){
		STILL_PLAYING[7] = 1;
	}
	else if(pthread_self() == TEAM_2_KEEPER){
		STILL_PLAYING[8] = 1;
	}
	else if(pthread_self() == TEAM_2_CHASER1){
		STILL_PLAYING[9] = 1;
	}
	else if(pthread_self() == TEAM_2_CHASER2){
		STILL_PLAYING[10] = 1;
	}
	else if(pthread_self() == TEAM_2_CHASER3){
		STILL_PLAYING[11] = 1;
	}
	else if(pthread_self() == TEAM_2_BEATER1){
		STILL_PLAYING[12] = 1;
	}
	else if(pthread_self() == TEAM_2_BEATER2){
		STILL_PLAYING[13] = 1;
	}
	
	if(pthread_self() == GOAL_1){
		SCORE_1 = 1;
	}
	else if(pthread_self() == GOAL_2){
		SCORE_2 = 1;
	}
}

void SIGUSR2_helper(int num){

  if(pthread_self() == TEAM_1_CHASER1){
    printf("Chaser1 from Team 1 is trying to Score...\n");
    pthread_kill(GOAL_2,SIGINT);
  }
  else if(pthread_self() == TEAM_1_CHASER2){
    printf("Chaser2 from Team 1 is trying to Score...\n");
    pthread_kill(GOAL_2,SIGINT);
  }
  else if(pthread_self() == TEAM_1_CHASER3){
    printf("Chaser3 from Team 1 is trying to Score...\n");
    pthread_kill(GOAL_2,SIGINT);
  }
  else if(pthread_self() == TEAM_2_CHASER1){
    printf("Chaser1 from Team 2 is trying to Score...\n");
    pthread_kill(GOAL_1,SIGINT);
  }
  else if(pthread_self() == TEAM_2_CHASER2){
    printf("Chaser2 from Team 2 is trying to Score...\n");
    pthread_kill(GOAL_1,SIGINT);
  }
  else if(pthread_self() == TEAM_2_CHASER3){
    printf("Chaser3 from Team 2 is trying to Score...\n");
    pthread_kill(GOAL_1,SIGINT);
  }
}

int main(){
  
  sem_init(&semaphore,0,1);

  BLUDGER.sa_handler = SIGINT_helper;
  BLUDGER.sa_flags = 0;

  USER_1.sa_handler = SIGUSR1_helper;
  USER_2.sa_flags = 0; 

  USER_2.sa_handler = SIGUSR2_helper;
  USER_2.sa_flags = 0; 

  pthread_create(&GOAL_1, NULL, goals, NULL);
	pthread_create(&GOAL_2, NULL, goals, NULL);

  sigaction(SIGINT,&BLUDGER,NULL);
  sigaction(SIGUSR1,&USER_1,NULL);
  sigaction(SIGUSR2,&USER_2,NULL);

  pthread_create(&SNITCH, NULL, Snitch, NULL);
  pthread_create(&BLUDGER_1,NULL,Bludger,NULL);
  pthread_create(&BLUDGER_2,NULL,Bludger,NULL);
  pthread_create(&QUAFFEL,NULL,Quaffle,NULL);


  pthread_create(&Team1_Seeker, NULL, Seeker1, NULL);
  pthread_create(&TEAM_1_KEEPER, NULL, Keeper, NULL);

  pthread_create(&TEAM_1_BEATER1, NULL, Beater, NULL);
  pthread_create(&TEAM_1_BEATER2, NULL, Beater, NULL);

  pthread_create(&TEAM_1_CHASER1, NULL, Chaser, NULL);
  pthread_create(&TEAM_1_CHASER2, NULL, Chaser, NULL);
  pthread_create(&TEAM_1_CHASER3, NULL, Chaser, NULL);

  pthread_create(&TEAM_2_SEEKER, NULL, Seeker2, NULL);
  pthread_create(&TEAM_2_KEEPER, NULL, Keeper, NULL);

  pthread_create(&TEAM_2_BEATER1, NULL, Beater, NULL);
  pthread_create(&TEAM_2_BEATER2, NULL, Beater, NULL);

  pthread_create(&TEAM_2_CHASER1, NULL, Chaser, NULL);
  pthread_create(&TEAM_2_CHASER2, NULL, Chaser, NULL);
  pthread_create(&TEAM_2_CHASER3, NULL, Chaser, NULL);
  
  pause();
}