//
//  main.c
//  a4
//
//  Created by Matt Loera on 3/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*typdef*/
typedef struct menuOptions menuOptions;
typedef void (*funcPtr)(int,char*[],int[]);

/*globals*/
const int NUM_OPTIONS = 7;
static char*MENU_TXT[] = {"Exit","Addition", "Subtraction","Multiplication","Division",
                         "Modulo","Reverse Input"};

struct menuOptions
{int n;char**options;};

const menuOptions menuData = {NUM_OPTIONS,MENU_TXT};

/*functions*/
void quit(int,char*[],int[]);
void addition(int,char*[],int[]);
void subtraction(int,char*[],int[]);
void multiplication(int,char*[],int[]);
void division(int,char*[],int[]);
void modulo(int,char*[],int[]);
void reverse(int,char*[],int[]);
void invalidInput(int,char*[],int[]);

int convert(int,char*[],int[]);
int menu(int,char*[],int[],int);
void displayMenu(menuOptions m);
int getUserInput(void);
void displayMath(int,int[],char,int);
void printStrReverse(char*);

/*array of func pointer*/
static funcPtr func[] = {quit,addition,subtraction,multiplication,division,modulo,reverse,invalidInput};

int main(int argc,char*argv[])
{
  int numbers[argc-1];
  int nonNumericArgs = 0;
  
  if(argc>16){
    printf("Too many args");
    return 1;
  }
  if(argc<3){
    printf("Not enough args");
    return 1;
  }

  nonNumericArgs = convert(argc-1,argv+1,numbers);
  return menu(argc-1,argv+1,numbers,nonNumericArgs);
}

/*definitions*/
int convert(int n,char*args[],int numbers[])
{
  int invalidConversions = 0;
  char* endptr=NULL;
  for(int i = 0; i < n; ++i){
    numbers[i] = (int)strtol(args[i],&endptr,0);
    if(*endptr != '\0') ++invalidConversions;
  }
  return invalidConversions;
}
int menu(int n,char*args[],int numbers[],int flag)
{
  int choice = 1;
  while(choice){
    displayMenu(menuData);
    choice = getUserInput();
    if(choice < 0 || choice > NUM_OPTIONS) choice = 7;
    func[choice](n,args,numbers);
  }
  return choice;
}
void displayMenu(menuOptions m)
{
  for(int i = 0; i < m.n;++i){
    printf("%d. %s\n",i,m.options[i]);
  }
  printf("Menu item: ");
}
int getUserInput()
{
  int choice = 0;
  if(scanf("%d",&choice)==0) choice = 8; //default for invalid input
  return choice;
}
void displayMath(int n, int numbers[],char operator,int result) //for use when displaying results
{
  //n guranteed to be at least 1
  printf("%d ",numbers[0]);
  for(int i = 1; i < n; ++i){
    printf("%c %d ",operator,numbers[i]);
  }
  printf("= %d\n",result);
}
void quit(int n,char*args[],int numbers[]) //choice 0
{}
void addition(int n,char*args[],int numbers[]) //choice 1
{ if(!n) return;
  int result = 0;
  for(int i = 0; i < n; ++i){
    result+=numbers[i];
  }
  displayMath(n,numbers,'+',result);
}
void subtraction(int n,char*args[],int numbers[]) //choice 2
{ if(!n) return;
  int result = numbers[0];
  for(int i=1;i<n;++i){
    result -= numbers[i];
  }
  displayMath(n,numbers,'-',result);
}
void multiplication(int n,char*args[],int numbers[]) //choice 3
{ if(!n) return; //no args
  int result = numbers[0];
  for(int i=1;i<n;++i){
    result *= numbers[i];
  }
  displayMath(n,numbers,'*',result);
}
void division(int n,char*args[],int numbers[]) //choice 4
{
  if(n<2) return; //not enough args
  if(numbers[1] == 0){
    printf("%d / 0 = -nan\n",numbers[0]);
    return;
  }
  float result = (float)numbers[0]/(float)numbers[1];
  printf("%d / %d = %f\n",numbers[0],numbers[1],result);
}
void modulo(int n,char*args[],int numbers[]) //choice 5
{
  if(n<2) return; //not enough args
  if(numbers[1] == 0){
    printf("denominator cannot be zero\n");
    return;
  }
  int result = (int)numbers[0] % (int)numbers[1];
  printf("%d mod %d = %d\n",numbers[0],numbers[1],result);
  
}
void reverse(int n,char*args[],int numbers[]) //choice 6
{
  if(!n) return; //no args
  printStrReverse(args[n-1]); //the last arg
  printf(" ");
  for(int i = n-2; i >= 0; --i){
    printStrReverse(args[i]);
    printf(" ");
  }
  printf("\n");
}
void printStrReverse(char* s)
{
  int len = (int)strlen(s);
  for(int i = len-1; i >= 0; --i){
    printf("%c",s[i]);
  }
}
void invalidInput(int n,char*args[],int numbers[]) //choice 7
{
  printf("Invalid selection. Try again. \n");
}
