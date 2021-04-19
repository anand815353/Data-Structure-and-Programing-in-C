#include <stdio.h>
#include <stdlib.h>


struct node
{
	int data;
	int row;
	int column;
	struct node *next;
};

struct List
{
	struct node *head;
	struct node *tail;
	int nonZero;
	int maxRow;
	int maxCol;
};

struct List *createList(int maxRow, int maxCol, int nonZero)
{
	struct List *l =NULL;
	l = (struct List*)malloc(sizeof(struct List));
	l->head = NULL;
	l->tail = NULL;
	l->nonZero = nonZero;
	l->maxRow = maxRow;
	l->maxCol = maxCol;
	
	return l;
}


void addAtEnd(struct List *l, int data,int row, int col)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->data = data;
	temp->row = row;
	temp->column = col;
	temp->next = NULL;
	
	if(l->head == NULL)
	{
		l->head = l->tail = temp;
	}
	else
	{
		struct node *temp1;
		temp1 = l->tail;
		temp1->next = temp;
		l->tail = temp;
		//free(temp1);
	}
	
}

void display(struct List *l)
{
	int i=0,e;
	e = l->nonZero;
	struct node *trv;
	trv = l->head;
	for(i = 0; i < e; i++)
	{
		printf("\n %d %d %d",trv->data,trv->row,trv->column);
		trv = trv->next;
	}
	free(trv);
	printf("\n");
}

void freeSpace(struct List *l)
{
    struct node *trv;
    
    while(l->head != NULL)
    {
        trv = l->head;
        l->head = l->head->next;
        free(trv);
    }
}

void fill(struct List *l, struct List *s)
{
	struct node *sum;
	struct node *temp;
	int i=0,j =0,flag =0,l_nonZero,count, val=0;
	count = s->nonZero;
	l_nonZero = l->nonZero;
	
	sum = s->head; 
	temp = l->head;
	
	
	for(i=0; i < l_nonZero; i++)
	{
		sum = s->head;
		for(j=0; j < count; j++)
		{
			if((temp->row == sum->row) && (temp->column == sum->column))
			{	
				flag=1;	
				break;
			}
			else
			{
				flag=0;
			}
			sum = sum->next;
		}
		if(flag==0)
		{
			val = temp->data;
			addAtEnd(s,val,temp->row, temp->column);
			count++;
		}
		temp = temp->next;
	}
	s->nonZero= count;
	//free(sum);
	free(temp);
	
}
void sparsSum(struct List *l_1, struct List *l_2, struct List *s)
{
	int i=0,j=0,flag =0,m1_nonZero, m2_nonZero,count=0, val=0;
	struct node *temp1;
	struct node *temp2;
	
	//sum = s->head; 
	m1_nonZero = l_1->nonZero;
	temp1 = l_1->head;
	
	m2_nonZero = l_2->nonZero; 
	temp2 = l_2->head;
	
	for(i=0; i < m1_nonZero; i++)
	{
		temp2 = l_2->head;
		for(j=0; j < m2_nonZero; j++)
		{
			if((temp1->row == temp2->row) && (temp1->column == temp2->column))
			{
				val = temp1->data + temp2->data;
				addAtEnd(s,val,temp1->row, temp1->column);
				count++;
			}
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}
	s->nonZero= count;
	
	fill(l_1, s);
	fill(l_2, s);
	
	free(temp1);
	free(temp2);
	
	
	
}

int main() 
{
	int maxRow,maxColumn,nonZero1,nonZero2,m1_row,m1_col,m2_row,m2_col,i,val;
	scanf("%d %d",&maxRow,&maxColumn);
	
	if(maxRow<=0 || maxColumn <= 0)
	{
	    printf("INVALID INPUT");
	    return 0;
	}
	
	scanf("%d %d",&nonZero1,&nonZero2);
	if((nonZero1 > maxRow*maxColumn) || (nonZero2> maxRow*maxColumn) || nonZero1 <0 || nonZero2 < 0)
	{
	    printf("INVALID INPUT");
	    return 0;
	}
	
	struct List *m_1 = createList(maxRow,maxColumn,nonZero1);
	for(i=0;i<nonZero1;i++)
	{
		scanf("%d %d %d",&m1_row,&m1_col,&val);
		if( m1_row >= maxRow|| m1_row < 0 || m1_col >= maxColumn || m1_col < 0  )
		{
		    printf("INVALID INPUT");
		    freeSpace(m_1);
	        return 0;
		}
		addAtEnd(m_1,val,m1_row, m1_col);
	}
	//display(m_1);
	
	
	struct List *m_2 = createList(maxRow,maxColumn,nonZero2);
	for(i = 0; i < nonZero2; i++)
	{
		scanf("%d %d %d",&m2_row,&m2_col,&val);
		if( m2_row >= maxRow || m2_row < 0 || m2_col >= maxColumn || m2_col < 0)
		{
		     printf("INVALID INPUT");
		     freeSpace(m_2);
	         return 0;
		}
		addAtEnd(m_2,val,m2_row, m2_col);
	}
	//display(m_2);
	
	struct List *sum = createList(maxRow,maxColumn,0);
	sparsSum(m_1, m_2, sum);
	//display(sum);
	
	int j=0,k=0, flag=0;
	struct node *trv;
	trv=sum->head;
	
	for(i=0; i< maxRow; i++ )
	{
		for(j=0;j <maxColumn; j++)
		{
			trv=sum->head;
			for(k=0; k< sum->nonZero; k++)
			{
				
				if((trv->row == i) && (trv->column == j))
				{
					printf(" %d",trv->data);
					flag=1;
					break;
				}
				trv = trv->next;
			}
			if(flag == 0)
			{
				printf(" 0");
			}
			else
			{
				flag=0;
			}
		}
		
	}
	free(trv);
	freeSpace(m_1);
	freeSpace(m_2);
	freeSpace(sum);
	
	return 0;
}

