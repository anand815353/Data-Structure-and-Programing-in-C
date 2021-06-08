/*Write a C program to check if a string has balanced parenthesis {}.

For example the string "abcd{  xyd{{0}}}" has valid balanced parenthesis. where as the string "abcd{{0123}{}" is not balanced.

Internally you should implemnent a stack using a single dimensional array and using the stack you need to solve balanced parethesis problem.

Input/Output Specification:
- If the string has balanced parenthesis your program should print 1 otherwise 0. String can contain any non-white space characters.

Sample Input/Output:

Input: abcd{xyd{{0}}}

Output: 1

Input: abc!,d{{0123}{}

Output: 0

Input: ab7879.,/-+

Output:1 */

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
