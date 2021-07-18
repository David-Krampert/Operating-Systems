#include <stdlib.h>

int rand(void);

int rand_r(unsigned int *seedp);

void srand(unsigned int seed);

int randomNumberGenerator()
{
  int lower = 0;
  int upper = 255;
  int ranNum = (rand() % (upper - lower + 1)) + lower; //holds the random number 
  return ranNum;
}



int main(int argc, char *argv[])
{
  int list[5]; //holds the input from users

  printf("Enter non-negative integers in ascending order: ");
  for(int i = 0; i < 5; i++)
  {
    scanf("%d", &list[i]);
    if(list[i] < 0)//check for negative numbers
    {
      printf("Negative numbers are not allowed!");
      return -1;
    }
    if(list[i] < list[i-1])
    {
      printf("The integer is not in ascending order");
      return -1;
    }
  }
  
  int len = sizeof(list)/sizeof(list[0]);

  srand(time(0)); // Use current time as seed for random generator 
  fork();
  int ranNum = randomNumberGenerator();
   printf("\n");
  printf("Random number:%d", ranNum);
  printf("\n");
  for (int j = 0; j <= len; j++)
  {
    if(j == len)
    {
      printf("\nThe random number %d is greater than all numbers in the list and the game is a tie.",ranNum);
      break;
    }
    if(ranNum > list[j])
    {
       if(ranNum < list[j+1])//the random number is less than the next in the list so j in the winning number
      {
        printf("The winning number is %d", list[j]);
        break;
      }

      if(j == len)//if ranNum is less than and its the last the game is a tie
      {
        printf("\nThe random number %d is greater than %d and the game is a tie.",ranNum, list[j]);
        break;
      }
        
    }
        
  }
  
  return 0;
}