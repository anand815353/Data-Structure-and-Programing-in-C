#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
	struct node *prev;
};

struct dLL
{
	struct node *head;
	struct node *tail;
};

struct dLL *createList()
{
	struct dLL *dll = (struct dLL*)malloc(sizeof(struct dLL));
	dll->head = NULL;
	dll->tail = NULL;
	
	return dll;
	
}
void display(struct dLL *d);

 void insertFirst(struct dLL *d, int data)
 {
 	struct node *temp = (struct node*)malloc(sizeof(struct node));
 	temp->data = data;
 	temp->next = NULL;
 	temp->prev = NULL;
 	
 	if(d->head == NULL)
 	{
 		d->head = d->tail = temp;
	}
 	else
 	{
 		d->head->prev =temp;
 		temp->next = d->head;
 		d->head = d->head->prev;
	}
 }
 
void insertLast(struct dLL *d, int data)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
 	temp->data = data;
 	temp->next = NULL;
 	temp->prev = NULL;
 	
 	if(d->head == NULL)
 	{
 		d->head = d->tail = temp;
	}
	else
	{
		d->tail->next = temp;
		temp->prev = d->tail;
		d->tail = d->tail->next;
	}
} 
int count(struct dLL *d)
{
	int count=0;
	if(d->head == NULL)
	{
		return -1;
	}
	struct node *trv;
	trv= d->head;
	count++;
	while(trv->next != NULL)
	{
		count++;
		trv = trv->next;
	}
	return count;
}
	
	
void insertAtIndex(struct dLL *d)
{
	int pos, i=1, size, val=0;
	size = count(d);
	scanf("%d", &pos);
	if((pos <0) || (pos> size && size !=-1 ))
	{
		printf(" INVALID INPUT\n");
		exit(0);
	}
	if((d->head == NULL) && (pos != 0))
	{
		printf(" INVALID INPUT\n");
		exit(0);
	}
	if(((d->head == NULL) && (pos == 0)) || (pos ==0))
	{
		
		scanf("%d",&val);
		insertFirst(d,val);	
		return;
	}
	if( pos == size)
	{
		scanf("%d",&val);
		insertLast(d, val);
	}
	else
	{
		struct node *temp1;
		temp1= d->head;
		
		scanf("%d",&val);
	
		struct node *temp = (struct node*)malloc(sizeof(struct node));
	 	temp->data = val;
	 	temp->next = NULL;
	 	temp->prev = NULL;
	 	
	 	while(i<pos)
	 	{
	 		temp1 = temp1->next;
	 		i++;
		}
		if(temp1 == d->tail)
		{	
			printf("----");
			return;
		}
		
		temp->prev = temp1;
		temp->next = temp1->next;
		temp1->next = temp;
		temp1 = temp1->next;
		temp1 = temp1->next;
		temp1->prev = temp;
	 	
	}
	
}



int removeFirst(struct dLL *d)
{
	if(d->head == NULL)
	{
		printf(" LE");
		return 0;
	}
	if(d->head->next == NULL)
	{
		printf(" %d", d->head->data);
		struct  node *trv;
		trv = d->head;
		d->head = d->tail =NULL;
		free(trv);
		
		return 0;
	}
	printf(" %d", d->head->data);
	struct node *trv;
	trv= d->head;
	d->head = d->head->next;
	d->head->prev = NULL;
	free(trv);
	

	return 0;	
}

int removeLast(struct dLL *d)
{
	if(d->head == NULL)
	{
		printf(" LE");
		return 0;
	}
	if(d->tail->prev == NULL)
	{
		printf(" %d", d->tail->data);
		struct  node *trv;
		trv = d->tail;
		d->head = d->tail =NULL;
		free(trv);
		
		return 0;
	}
	printf(" %d", d->tail->data);
	struct  node *trv;
	trv = d->tail;
	d->tail = d->tail->prev;
	d->tail->next = NULL;
	free(trv);
	
	return 0;
}

int removeAtIndex(struct dLL *d)
{
	int index, i=0, size, val=0;
	size = count(d);
	scanf("%d", &index);
	if((index <0) || (index> size-1 && size !=-1))
	{
		printf(" INVALID INPUT\n");
		exit(0);
	}
	if(d->head == NULL)
	{
		printf(" LE");
		return 0;
	}
	if((d->head->next == NULL) && (index !=0))
	{
		printf(" INVALID INPUT");
		exit(0);
	}
	if(index == 0)
	{
		removeFirst(d);
		return 0;
	}
	if( index == size-1)
	{
		removeLast(d);
	}
	else
	{
		struct node *trv;
		trv = d->head;
		
		while(trv != d->tail)
	 	{
	 	    if(i==index-1)
	 	    {
	 	        break;
	 	    }
	 		trv = trv->next;
	 		//printf("%d", i);
	 		i++;
		}
		//trv = trv->prev;
		if(trv == d->tail)
		{	
			printf("exception");
			return 0;
		}
		//printf(" --%d--", trv->data);
		

		
		trv= trv->next;
		struct node *temp;
		struct node *temp1;
		temp = trv->prev;
		temp1 = trv->next;
		//temp = temp->next;
		//temp = temp->next;
		//temp1 = temp1->next; 
		
		temp->next = temp1;
		temp1->prev = temp;
		 
		printf(" %d", trv->data);
		free(trv);
		
	}	
	
	return 0;
}

void display(struct dLL *d)
{
    int size;
    size= count(d);
	if(d->head == NULL)
	{
		printf("List empty \n");
	}
	/*if(size== 0)
	{
	    printf(" %d", d->head->data);
	    return;
	}*/
	else
	{
	    int i = 0;
		struct node *trv;
		trv = d->head;
		while(i<size-1)
		{
			printf(" %d",trv->data);
			if(trv->next == NULL)
			{
			    break;
			}
			trv = trv->next;
			i++;
		}
		printf(" %d", trv->data);
	}
}

void destroy(struct dLL *d)
{
	struct node *trv;
	
	while(d->head != d->tail)
	{
		trv = d->head;
		d->head = d->head->next;
		free(trv);
	}
	d->head = d->tail = NULL;
	//free(d);
}

int main()
{
	int i=0,e=0, p=0;
	struct dLL *d = createList();
	
	while(1)
	{
		scanf("%d", &i);
		if(i == -1)
		{
		    destroy(d);
		    return 0;
		}
		switch(i)
		{
			case 1: 
				scanf("%d",&e);
				insertFirst(d,e);
				break;
			case 2:
				scanf("%d",&e);
				insertLast(d,e);
				break;
			case 3:
				insertAtIndex(d);
				break;
			case 4:
				removeFirst(d);
				break;
			case 5:
				removeLast(d);
				break;
			case 6:
				removeAtIndex(d);
				break;
			case 7:
				display(d);
				break;
			case -1:
			    exit(1);
				break;
			default:
			    printf(" INVALID INPUT");
			    exit(0);
				break;
			/*case 8:
				printf("no of elements in the list:  %d",count(d));
				break;*/
		}
	}
	
	return 0;
}


