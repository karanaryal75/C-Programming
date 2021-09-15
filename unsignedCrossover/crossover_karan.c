/**************************/
/*Karan Aryal             */
/*CS 241 Section 01       */
/*Lab: Crossover          */
/**************************/

#include<stdio.h>
#include<stdlib.h>
// Setting an array with size 16
char firstPosition[16];
char secondPosition[16];
char thirdPosition[16];
unsigned short crossover(unsigned short a, unsigned short b, int n)
{
  int i;
  //Converting decimal number to binary
  //and keeping its value from end.
  for(i = 15; i >=0; i--)
  {
    firstPosition[i] = a % 2;
    a = a/2;
  }
  //Same thing with number b
  for(i = 15; i>=0;i--)
  {
    secondPosition[i] = b % 2;
    b =b/2;
  }
  i = 0;
  int j = 0;
  //Swaping value and storing it in third array
  for(; i< 16-n;i++)
  {
    thirdPosition[j] = secondPosition[i];
    j++;
  }
  //Swaping remaining value and storing it in third array
  for(; i <16; i++)
  {
    thirdPosition[j] = firstPosition[i];
    j++;
  }
  //Storing value and returning it
  int result = 0;
  for (i=0; i<16; i++)
  {
    result = result * 2 + thirdPosition[i];
  }
  return result;
}

int main()
{
  int count, numspace, chr;
  count= numspace = 0;
  //Reading character from input file
  while((chr= getchar()) != EOF)
  {
    //if character doesnot contain new line then this loop is true
    if(chr!= '\n')
    {
      //if character doesnot contain spaces and is between 0 to 9 
      if(chr!= ' ' && chr!='.' && chr >= '0' && chr<='9' )
      {
	//Reading spaces and setting up conditions.
	if( numspace == 0)
	{
	  //if spaces are not present all characters are stored in first array
          firstPosition[count] = chr;
	  count++;
	}
	else if (numspace == 1)
	{
	  //if space count is 1 then characters are stored in second array
	  secondPosition[count] = chr;
          count++;
	}
	else if (numspace == 2)
	{
	  //if space count is 2 then character are stored in third array
	  thirdPosition[count] = chr;
	  count++;
	}
	
      }
      else if ( chr = ' ')
      {
	//if character is space numspace is incremented then count is reset 
	if(numspace == 0)
	{
	  numspace++;
	  count=0;
	}
	else if (numspace == 1)
	{
	  numspace++;
	  count=0;
	}
      }
    }
    //if character is a new line
    else if ( chr=='\n')
    {
      // Error checking, if numspace is more than 2 or numspace is one.
      if(numspace > 2 || numspace == 1 )
      {
        printf("error\n");
      }
      else
      {
	//Converting character to integer using atoi library function.
	int a = atoi(firstPosition);
	int b = atoi(secondPosition);
        int n = atoi(thirdPosition);
        int total = crossover(a,b,n);
	//If given number is more that 16 the program gives an error.
	if (n > 16)
	{
	  printf("error\n");
	}
	else
	{
        //Prints result of given numbers
	printf("%d\n", total);
	}	
      }
      //Resets count and numspace to zero
      count = 0;
      numspace = 0;
    }      
  }
  return 0;
}

