/*Write a C program to check is a given string is palindrom or not.

Internally you should implement stack and queue and using both the stack and queue you should check if a given string is palindrom or not.


Sample Input/Output:
Input: abcdabcd
Output: 0

Input: abcddcba
Output: 1 */


#include<stdio.h>
#include<stdlib.h>

#define SIZE 50

int top=-1,front=-1,rear=-1,size=SIZE;
char stack[SIZE],queue[SIZE];

void enqueue(char c)  //enqueue's element in the queue.
{
    if(rear==size-1)  // overfolow condititon
    {
        //printf("--2--");
        exit(1);
    }
    if(front==-1)
    {
        front=0;
    }
    queue[++rear]=c;
}

char dequeue()  // dequeue's element from front of queue.
{
    if(front==-1 || front>rear) //underflow condition
    {
        //printf("--3--");
        return 0;
    }
    
    /*if(front>rear)
    {
        front=rear=-1;
        return 0;
    }
    else
    {*/
    
    return queue[front++];  //dequeue
    
    //}
}

void push(char c)
{
    if(top>SIZE)
    {
        //printf("--4--");
        exit(1);
    }
    stack[++top]=c;
}

char pop()
{
    //printf("--5--");
    return stack[top--];
}

int main()
{
    int count=0,loop=0,flag=1;
    char exp[SIZE],ch;
    
    fgets(exp,SIZE,stdin);
    //puts(exp);
    
    while((ch=exp[count++])!='\n')
    {
        push(ch);
        enqueue(ch);
    }
    
    while(count>1)
    {
        if(dequeue()!=pop())  //if dequeue from queue is not equal to pop from stack then flag=0 i.e its not palindrome and no need to check further.  
        {
            flag=0;
            break;
        }
        count--;
    }
    printf("%d",flag);
    
    return 0;
}
