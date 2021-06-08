/* Implement a generic single linked list in C.
Using the implemented generic single linked list, implement Radix sorting technique to sort positive integer numbers.

Input/Output Specification:
Input is a sequent of positive numbers:
n i1 i2 i3 i4 ... in

n: number of elements to sort (n > 0)
ik: kth element of the list (ik >= 0 for all k)

-If input is invalid display INVALID INPUT
-otherwise display the sorted array

Sample Input/Output:
Input: 6 20 100 30 40 90 200
Output: 20 30 40 90 100 200 */


#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};

struct List
{
	struct node *head;
	struct node *tail;
	int count;
};

struct List *createList()
{
	struct List *l = NULL;
	l  = (struct List*)malloc(sizeof(struct List));
	l->head = NULL;
	l->tail = NULL;
	l->count = 0;	
	
	return l;
}
void display(struct List *l);

void addAtEnd(struct List *l, int data, int size)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->data = data;
	temp->next = NULL;
	//printf("%d", temp->data);
	
	if(l->head == NULL)
	{
		l->head = l->tail =  temp;
		l->count = size;
	}
	else
	{
		
		l->tail->next = temp;
		l->tail = l->tail->next;
		//printf("%d", l->tail->data);
	}
}

int largest(struct List *l)
{
	int large = 0,i = 0; 
	
	struct node *trv;
	trv = l->head;
	
	while(i < l->count)
	{
		if(trv->data > large)
		{
			large = trv->data;
		}
		trv = trv->next;
		i++;
	}
	
	return large;
	
}
int extractDigit(int number, int k)
{
	int term =0, count;
	for(count =1; count<=k; count++)
	{
		term= number %10;
		number =number /10;
	}
	return term;
}

void radixSort(struct List *l)
{
	int large = 0, passRequired=0,pass,i, bucket,count=0,digit=0;
	large = largest(l);
	struct node *r[10], *f[10];
	while(large > 0)
	{
		passRequired++;
		large = large/10;
	}
	
	for(pass = 1; pass <= passRequired; pass++)
	{
		//printf("pass -- %d \n", pass);
		for(bucket =0 ; bucket<10; bucket++)
		{
			r[bucket] = NULL;
			f[bucket] = NULL;
			//printf("1");
		}
		i=0;
		struct node *trv;
		
		for(trv = l->head; trv != NULL; trv=trv->next)
		{
			digit = extractDigit(trv->data, pass);
			//printf("Digit %d \n", digit);
			
	
			if(f[digit] == NULL)
			{
				f[digit] = trv;
		
			}
			else
			{
				r[digit]->next =trv;
			
			}
			r[digit] = trv;
		}
		count =0;
		while(f[count] == NULL)
		{
			count++;
		}
		l->head = f[count];
		while(count<9)
		{
			if(r[count+1] != NULL)
			{
				r[count]->next = f[count+1];
			}
			else
			{
				r[count+1] = r[count];
			}
			count++;
		}
		r[9]->next =NULL;
		//display(l);

	}
	
	
	
}

void display(struct List *l)
{

	if(l->head == NULL)
	{
		printf("empty");
	}
	else
	{ int i=0;
		struct node *trv;
		trv = l->head;
		while(i < l->count)
		{
			printf("%d ", trv->data);
			trv = trv->next;
			i++;
		}
		//printf("%d \n",trv->data);
	}
}

int main()
{
	int count,val,i;
	scanf("%d", &count);
	if(count<=0)
	{
	    printf("INVALID INPUT");
	    return 0;
	}
	struct List *l= createList();
	for(i=0;i<count;i++)
	{
		scanf("%d",&val);
		
		if(val<0)
	    {
	        printf("INVALID INPUT");
	        return 0;
	    }
		addAtEnd(l, val, count);
	}
	
	radixSort(l);
	
	struct node *trv;
	trv= l->head;
	while(trv != NULL)
	{
		printf(" %3d ", trv->data);
		trv= trv->next;
	}
	printf("\n");
	return 0;
}

