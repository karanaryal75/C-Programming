/************************************/
/* Karan Aryal                      */
/* CS 241 section -004              */
/* 02/11/2020                       */
/************************************/
#include <stdio.h>
#define IN 1
#define OUT 0
#define n 7
int main()
{
  /**Initializing variables*/
  int chr,num,temp;
  int isWord, chrCount, newLine;
  int word, count, state;
  /**Setting their value to zero*/
  chrCount = newLine = 0;
  word = count = 0;
  isWord = state = OUT;
  temp =  0;
  num = 1;
  printf("%d. ",num);
  /**Reading each character until end of file.*/
  while (((chr  = getchar()) != EOF) )  
  {  
    /**Finding word by counting space, new line or tabs.*/
    if ( chr == ' ' || chr == '\n' || chr == '\t' )
    {
      isWord = OUT;
    }
    else if (isWord == OUT) 
    {
      isWord = IN;
      temp ++;
      word ++;
    }
    /**Counting number of lines*/
    if (chr == '\n')
    {
      num++;
      newLine++;
    }
    else
    { 
    /**Counting number of characters*/
      count++;
    }
    
    if (chr != '\n')
    {
      /**Counting number of character in a line*/
      chrCount++;
      /**Shifting characters*/
      if (chr >= 'a' && chr <= 'z')
      {
        chr = (char) (((chr - 'a' + n) % 26 ) + 'a');
        printf("%c", chr);
      }
      else if (chr >= 'A' && chr <= 'Z')
      {
	chr = (char) (((chr-'A' + n) %26) + 'A');
	printf("%c", chr);
      }
      else
      {
        printf("%c",chr);
      }
    } 
    
    else if (chr == '\n') 
    {
      /**Printing out word and character count.*/
      printf(" (%d,%d)\n", temp, chrCount);
      if (num < 6)
        printf("%d. ", num);
      chrCount = 0;
      temp = 0;
    }    
  }
  return 0;
}
