/**************************/
/*Karan Aryal             */
/*05 September 2019       */
/*CS-241 Section-01       */
/**************************/
#include<stdio.h>
int main()
{
  int chr,total,count;
  total = 0;
  count = 0;
  // Checking whether line is end of function.
  while((chr=getchar()) != EOF ){
    //Using condtion to check spaces present in each line.
    if (chr == '\n'){
    // If true, prints the sum.
      if (count % 4 == 0){
        printf("%d\n",total);
      }else{
        printf("error\n");
      }
    // after each line reset total and count to zero. 
      total=0;
      count=0;
    }
    // If line doesnot have any spaces,linebreak then loop starts. 
    else if(chr!='\n' && chr!=' ' && chr >='0' && chr<='9'){
      count++;
    // seperating numbers in 4 digits and adding them.
      if(count % 4 == 1){
        total = total+(chr-'0')*1000;
      }
      else if (count % 4 == 2){
        total = total+(chr-'0')*100;
      }  
      else if (count % 4 == 3){
        total = total+(chr-'0')*10;
      }
      else if (count % 4 == 0){
        total = total+(chr-'0');
      }
    }  
  }
  return 0;
}

