#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node                 //doubly linked list
{
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head;
struct node *rear;

void insertLinkedList(int digit)  //inserting digits in linked list
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data=digit;
    if(head == NULL)
    {
        temp->next = NULL;
        temp->prev = NULL;
        head = rear = temp;
    }
    else
    {
        temp->prev = rear;
        rear->next = temp;
        temp->next = NULL;
        rear = temp;
    }
}

int extractDigits(int n)
{
    int r=0,count=0;
    while(n!=0)             //loop to extract individual digits from number 
    {
        r = n % 10;             //gets remainder which is last digit of the number enterd
        insertLinkedList(r);
        count++;                //counts no of digits
        n = n / 10;
    }
    rear->next=head;
    head->prev=rear;
    return count;
}

int checkPrime(int n)
{
    int flag=0,i=0;
    if(n == 2)
    {
        flag = 1;
    }
    else
    {
        for(i = 2; i <= ceil(sqrt(n)); i++)
        {
            if(n % i == 0)
            {
                flag = 0;
                break;
            }
            else
            {
                flag = 1;
            }
        }
    }
    
    return flag;
}

int main()
{
    int n, flag=0, count = 0, number = 0, loop = 0, digitLoop = 0;
    struct node *start;
    struct node *trv;
    
    scanf("%d", &n);
    
    if(n<=0)
    {
        flag=-1;
    }
    
    else
    {
        count = extractDigits(n);
        start = rear;
        do
        {
            trv = start;
            do
            {
                number = number * 10 + trv->data;
                trv = trv->prev;
                digitLoop++;
            }while(digitLoop < count);
            
            flag = checkPrime(number);
            if(flag == 0)
            {break;}
            
            number=0;
            digitLoop=0;
            
            start = start->prev;
            loop++;
        }while(loop < count);
    }
    printf("%d", flag);
    
    return 0;
}
