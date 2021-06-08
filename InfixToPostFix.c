/* Implement a stack using linked lists.

Using the implemented stack write program to convert an infix expression to postfix expression.

Input/Output Specification:
-Input expression will consists of single letter variables and integer constants
-Only binary operators +, -, *, / and % will be allowed
-brackets () can be used in the infix expression
-Operator precedence is same as the C language
-You can assume that infix expression is a valid infix expression.

Sample Input/Output:

Input: a + b * c + (d * e + f) * 10
Output: a b c * + d e * f + 10 * +     

 */


#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct node
{
	char data;
	struct node *next;
};

struct stack
{
	struct node *base;   //base of stack is constant and doesnot change in the program
	struct node *stackTop; //stackTop changes as elements gets filled in. 
	int size;              //fixed size of stack through out program and dynamically alloted based on number of input character 
	int top;                // count of current elements in the stack top =-1 means stack is empty, top=0 means  stack has an element 
};

struct stack *createStack(int maxSize)
{
	struct stack *s = (struct stack*)malloc(sizeof( struct stack));
	s->base =NULL;
	s->stackTop = NULL;
	s->size = maxSize;
	s->top = -1;
	
	return s;
}

int isEmpty(struct stack *s)
{
	if(s->top <0)  //top =-1 means stack is empty, top=0 means  stack has an element 
	{
		return 1;
	}
	return 0;
}

int isFull(struct stack *s)
{
	if(s->top == s->size)
	{
		return 1;
	}
	return 0;
}

void push(struct stack *s, char data)
{
	struct node *temp= (struct node*)malloc(sizeof(struct node));
	temp->data = data;
	temp->next = NULL;
	if(isEmpty(s) == 1)
	{
		s->base = s->stackTop = temp;
		s->top = s->top+1; 
	}
	else if (isFull(s) == 1)
	{
		printf("stack is FULL");
	}
	else
	{
		s->stackTop->next = temp;
		s->stackTop = s->stackTop->next;
		s->top = s->top + 1;
	}
}
void displayStack(struct stack *s)
{
	if(isEmpty(s) == 1)
	{
		printf("stack is Empty");
	}
	else
	{
		struct node *temp;
		temp = s->base;
		//int i=0;
		while(temp->next != NULL)
		{
			printf("%c ", temp->data);
			temp = temp->next;
		}
		printf("%c \n", temp->data);
		free(temp);
	}
}

char pop(struct stack *s)
{
	if(isEmpty(s) == 1)
	{
		printf("stack is Empty");
		return -1;
	}
	struct node *temp;
	temp = s->stackTop;
	//printf("TOP %d \n", s->top);
	
	int i = 1,flag=0;
	s->stackTop = s->base;
	char c = temp->data;
	
	while(s->stackTop->next != temp)
	{
		//printf(" traverse %c", s->stackTop->data);
		if(s->stackTop->next == NULL)
		{
			flag=1;
			break;
		}
		else
		{
			s->stackTop= s->stackTop->next;
		}
	}
	//printf(" traverse %c \n", s->stackTop->data);
	s->top = s->top - 1;
	if(flag==1)
	{
		s->base =NULL;
		s->stackTop = NULL;
		//printf("new TOP %d \n", s->top);
		free(temp);
		return c;
	}
	//printf("new TOP %d \n", s->top);
	s->stackTop->next = NULL;
	free(temp);
	return c;
}


char getTop(struct stack *s)
{
    if(s->top<0)
    {
        return 0;     //if top is empty then returns Zero
    }
	return s->stackTop->data;
}


int preAsso(char top, char c)
{
    int flag = 0;
    if (( c == '*' || c == '/' || c == '%') && (top == '+' || top == '-'))
    {
        flag = 1;  // 1 = push
    }
    else if(( c == top)  || (c == '+' && top ==  '-')) // || ( c == '%' && top == '%') || (c == '*' && top == '*') || (c == '/' && top == '/'))
    {
        flag = 2; // 2  = pop then push;
    }
    else if (( c == '/' && top == '%') || (c == '*' && top == '%') || (c == '*' && top == '/'))
    {
        flag = 2;
    }
    else if ((top == '%' || top == '/' || top == '*' ) && (c == '+' || c== '-'))
    {
        flag = 2;
    }
    else
    {
        flag = 1;
    }
    
    return flag;
}





int main()
{
	int i=0, flag =-1, stackSize=0;
    char infx[100], ch, top;
    fgets(infx, 100, stdin);
	while(infx[++stackSize] != '\n');  // size of stack is dynamic alloted based  on no of chartecter input  
	struct stack *s = createStack(stackSize);
	
	
	while((ch =infx[i++]) != '\n')
    {
        //printf("%c", ch);
        if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '(' || ch == ')')
        {
            if(isEmpty(s) == 1 || ch == '(')
            {
                push(s, ch);
            }
            /* else if(ch == getTop(s))
            {
                printf("%c", pop(s));
            }*/
            else if(ch == ')')
            {
                top = pop(s);
                
                while(top != '(')
                {
                    if(top == '(')
                    {
                        break;
                    }
                    else 
                    {
                        printf("%c ", top);
                    }
                    
                    top = pop(s);
                }
            }
            
            else
            {
                top = getTop(s);
                flag = preAsso(top, ch);
                
                if(flag == 1)
                {
                    push(s,ch);
                }
                else if(top == ch)
                {
                    printf("%c", ch);
                }
                else if( flag == 2)
                {
                    printf("%c", pop(s));
                    printf(" ");
                    flag = preAsso(getTop(s), ch);
                    if(flag == 2)
                    {
                        printf("%c", pop(s));
                        //printf(" ");
                    }
                    push(s,ch);
                }
                else
                {
                    printf("exception");
                }
                
            }
            
        }
        
    else
        {
            printf("%c",ch);
        }
    }
	
	while(s->top >=0 )
	{
	printf("%c", pop(s) );
	//displayStack(s);
	}
	free(s);
	
	
	return 0;
}
