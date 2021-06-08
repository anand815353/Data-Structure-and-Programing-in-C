/*Implement an efficient and scalable stack using arrays.
The stack should have the following features:
1. Initial size of the stack is 4 element
2. Stack in meant to hold integer values
3. Stack has the following functions:
    -createStack() - creates a stack dynamically
    -push(S, e) - push element e onto the stack
    -pop(S) - delete element from the stack using LIFO mechanism
    -getTop(S) - returns the top element of the stack
4. If push(S, e) is called when stack is full, stack size to be doubled and memory to be reallocated.

Now write a test function main() which evaluates a post-fix expression. Only binary operators +, -, * and / (integer division) to be used in the post-fix expression.

Sample Input:10 20 30 + +
output: 60

Input: 10 20 30 / -
Output: 10 */


#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct stack
{
    int *data;
    int size;
    int top;
};

struct stack* createStack(int max)
{
    struct stack *s = NULL;
    s = (struct stack*)malloc(sizeof(struct stack));
    s->data = (int*)malloc(sizeof(int) * max);
    s->size =max;
    s->top = -1;
    
    return s;
}

void push(struct stack *s, int c)
{
    if(s->top == s->size-1)
    {
        int i;
        int *temp  = s->data;
        s->data = malloc(sizeof(int) * 2 * s->size);
        s->size = 2 * s->size;
        
        for(i=0; i <= s->top; i++)
        {
            s->data[i] = temp[i];
        }
        free(temp);
    }
    s->data[++s->top] = c;
}

int pop(struct stack *s)
{
    if(s->top < 0)
    {
        exit(1);
    }
    return s->data[s->top--];
}

int getTop(struct stack *s)
{
    if(s->top < 0)
    {
        exit(1);
    }
    return s->data[s->top];
}

int main()
{
    struct stack *s = createStack(4);
    
    int i=0, op1=0,op2=0,flag=1;
    char pofx[50],ch;
    fgets(pofx,100,stdin);
    
    while((ch=pofx[i++])!='\n')
    {
        if(isdigit(ch))
        {
            if(flag==0)
            {
                push(s,pop(s) * 10 + (ch-'0'));
            }
            else
            {
                push(s, ch-'0');
                flag=0;
            }
        }
        else if(ch==' ')
        {
            flag=1;
        }
        else
        {
            op2=pop(s);
            op1=pop(s);
            switch(ch)
            {
                case '+': push(s, op1 + op2);break;
                case '-': push(s, op1 - op2);break;
                case '*': push(s, op1 * op2);break;
                case '/': push(s, op1 / op2);break;
                default: break;
            }
        }
        
        
    }
    printf("%d",getTop(s));
    
    return 0;
}
