/************************************/
/* Karan Aryal                      */
/* CS 241 section -004              */
/* 02/11/2020                       */
/************************************/
#include <stdio.h>
#define n 7
int main()
{
  /**Initializing variables*/
  int chr;
  /**Reading each character until end of file.*/
  while (((chr  = getchar()) != EOF) )  
  {     
    if (chr != '\n')
    {
      /**shifting character by reading the encrypt file*/
      if (chr >= 'a' && chr <= 'z')
      {
        chr = (char) (((chr - 'z' - n) % 26 ) + 'z');
        printf("%c", chr);
      }
      else if (chr >= 'A' && chr <= 'Z')
      {
	chr = (char) (((chr - 'Z' - n) %26) + 'Z');
	printf("%c", chr);
      }
      else
      {
        printf("%c",chr);
      }
    }  
    else if (chr == '\n') 
    {
      /**prints new line*/
      printf("\n");
    } 
  }
  return 0;
}
