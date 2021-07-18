#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int count = 0;

void sigint(int sig)
{
    printf("You pressed ctrl-c %d times\n", ++count);
}

void signal_callback_handler(int signum)
{
  /* print signal num and description*/
  printf("\nSignal number: %d\n",signum);
  printf("\nSingal description: %s\n",strsignal(signum));
}

int main()
{
  alarm(30); //scheduled alarm for 30 seconds so program is killed after 30 seconds
  /*set up signal handler*/
  signal(SIGINT, sigint);
  sigset_t signal_set;

  /*add SIGINT to singal_set*/
  sigaddset(&signal_set, SIGINT);
  fflush(stdout);

  /*block the SIGINT signal*/
  sigprocmask(SIG_BLOCK, &signal_set, NULL);
  sleep(10);
  sigset_t pending_set;

  /*get pending signal set*/
  sigpending(&pending_set);
  fflush(stdout);

  /*ignore SIGINT*/
  signal(SIGINT, SIG_IGN);
  sigset_t pending_set1;

  /*get pending signal set again*/
  sigpending(&pending_set1);

  fflush(stdout);

  /*set up another singal handler*/
  signal(SIGINT, signal_callback_handler);
  sigset_t signal_set1;

  /*add SIGINT to singal_set*/
  sigaddset(&signal_set1, SIGINT);
  fflush(stdout);

  /*unblock the SIGINT signal*/
  sigprocmask(SIG_UNBLOCK, &signal_set1, NULL);

  /*sleep for 10 secs*/
  sleep(10);

  
  while(1){}
}