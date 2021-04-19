#include<stdio.h>
#include<stdlib.h>

#define SIZE 50   //size of stack 

int top=-1;
char stack[SIZE];

void push(char c)
{
    if(top>SIZE)
    {
        exit(1);
    }
    stack[++top]=c;
}

void pop()
{
    //if(top<-1)
    //{
      //  exit(1);
    //}
    stack[top--];
}

int main()
{
    int i=0;
    char exp[SIZE],ch;
    fgets(exp,SIZE,stdin);  // BUG: if length of text is greater than SIZE(50) then segmentation fault.
    //puts(exp);
    
    while((ch=exp[i++])!='\n')
    {
        if(ch=='{')         // if "{" then only it will push 
        {
            push(ch);
        }
        if(ch=='}')
        {
            pop();
        }
    }
    
    if((top>-1)||(top<-1))  // logic: if stack is empty then paranthesis are balanced 
                                //if top goes to negative then also its unbalaced in case of }}}}} 
                                // in case of }}}{{{ which is balaced, top will trace back to top=-1  when {{{ are given
    {
        printf("0");
    }
    else
    {
        printf("1");
    }
    
    return 0;
}
