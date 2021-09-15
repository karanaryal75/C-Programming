/*******************************/
/* Karan Aryal                 */
/* CS 241                      */
/* October 4, 2019             */
/*******************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


char rank[13] = "A23456789XJQK";
char suit[4] = "CHDS";
char cardDeck[104];
int numDeck, numCard;
int offHand_Deck[20];

//Sorting an Array in a ascending order
void orderedList(int d[])
{
  int x;
  for(int i = 0; i<numCard; i++)
  {
    for(int j = i+1; j<numCard; j++)
    {
      //Swapping if the condition is true
      if(d[i] > d[j])
      {
        x = d[i];
	d[i] = d[j];
	d[j] = x;
      }
    }
  }
}

int main()
{
  srand((unsigned long)time(NULL));
  int num_type, count;
  int x = 0;
  int a = 0;
  int b = 1;
  bool isPut = false;
  //Initilize Deck
  for(int m=0; m<13; m++)
  {
    for(int n=0; n<4;n++)
    {
      //Even position keeping rank, odd position keeping  suit
      cardDeck[a] = rank[m];
      cardDeck[b] = suit[n];
      a = a+2;
      b = b+2;
    }
  }
  int chr;
  //Reading character from input file.
  while((chr=getchar()) != EOF)
  {
    //Number of deck present in the input
    if(isdigit(chr) && count == 0)
    {
      numDeck = chr -'0';
      count++;
    }
    //Number of suits found in the given deck
    else if(isdigit(chr) && count == 1)
    {
      numCard = chr -'0';
      count++;
    }
    //After reading new line, evaluating..
    else if(chr == '\n')
    {
      for(int g =0; g<numDeck;g++)
      {
        while(x<numCard)
        {
	//Random number is generated
	  num_type = rand()%103;
	  int take1;
	  //Storing number in order
	  if(num_type % 2 ==0)
          {
            take1 = num_type;
	  }
	  else
	  {
	    take1 = num_type+1;
	  }
	  for(int y = 0; y<numCard; y++)
	  {
	  //Ignoreing repeating number
	    if(take1 == offHand_Deck[y])
	    {
	      isPut=true;
	      break;
	    }
	    else
	    {
	      isPut=false;
	    }
	  }
	  //Keeping random number in an array
	  if(isPut==false)
	  {
	    offHand_Deck[x]=take1;
	    x++;
	  }
	}
	//Sorting the deck
	orderedList(offHand_Deck);
	int take2;
	//Card is printed
	for(int y=0; y<numCard; y++)
        {
	  take2 = offHand_Deck[y];
	  //Checking if card is not the last card to avoid comma
	  if(y != numCard-1)
	  {
	    printf("%c", cardDeck[take2]);
	    printf("%c,", cardDeck[take2 + 1]);
	  }
	  else
	  {
	  //Printing the card
	    printf("%c", cardDeck[take2]);
	    printf("%c", cardDeck[take2 + 1]);
	  }
	}
	//Prints five spaces between hands
	printf("     ");
        x = 0;
      }
      //Printing new line
      printf("\n");
      //Resetting count to zero
      count = 0;
    }
  }
  return 0;
}
