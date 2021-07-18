//David Krampert
//
//
//
//
///////////////////////////////////////////////////////////////////////////////

// Includes -------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//Main Function

int main(int args, const char* argv[])
{

  //Welcome message
  printf("\n");
  printf("===========================================\n");
  printf("Welcome to myShell. A program wrtten by me\n");
  printf("===========================================\n");
  printf("\n");
  printf("\n");

//delcare variables------------------------------------------------------------
  //alocating space for cwd_buf
  char cwd_buf[500];

  //size should be the size of whatever element that is being used in the call
  size_t size = sizeof(char);

  //to hold user input
  char* userInput = (char*)malloc(sizeof(char) * 100);

  //boolean to exit the program when "exit" is entered
  int exit_bool = 1; //1 = false, 0 = true

  //parent process: child's exit status
  int status;

 //variable to store the child's pid
  pid_t child_pid;

  char *input_arr[100];

  const char delim[2] = " ";

//------------------------------------------------------------------------------
 while( exit_bool == 1 )
  {
    getcwd(cwd_buf, 500);//gets pathname of current working directory

    printf("%s ? ", cwd_buf);//prints the current workinng directory
    scanf("%[^\n]%*c", userInput);//gets input from user

    //tokenize the user input command into directive
    char* directive;
    directive = strtok(userInput, delim);

    int i = 0;
    while(directive != NULL)
    {
        //loads the tokenized input stored in "directive" into the input_arr array
        input_arr[i] = directive;
        directive = strtok(NULL, delim);
        i++;
    }

    //Do commands--------------------------------------------------------------


    //if the user enters "exit" the program will stop
    if( strcmp((input_arr[0]),  "exit") == 0 )
    {
        exit_bool = 0;//exit is true
        printf("\nThe program was killed\n");
        exit(1);
    }
    //else if the user enters "cd" the current directory will be changed
    else if( strcmp(input_arr[0], "cd") == 0 )
    {
        //char* path = strtok(NULL, delim);//tok the next word in the string
        chdir( input_arr[1] );//change the directory
        printf("\nDirectory changed to %s\n", input_arr[1]);//print the new directory
    }
    //else the user enters anything else exec is used to handle the UNIX command
    //fork a child process
 else
    {
        child_pid = fork();//create child
        if(child_pid == 0)//child
        {
          execlp(input_arr[0], input_arr[0], input_arr[1], (char*)0);
        }
        else
        {
          wait(NULL);
        }
       fflush(stdout);
    }//end of else




  }//end of while loop

  return 0;
}//end of main
