#include <stdio.h>
#include <stdlib.h>

struct queue
{
    int *data;
    int maxsize;
    int size;
    int front;
    int rear;
};

struct queue* createQueue(int max)
{
    struct queue *q = NULL;
    q =(struct queue*) malloc(sizeof(struct queue));
    q->data = (int*)malloc(sizeof(int) * max);
    
    q->maxsize = max;
    q->size = 0;
    q->front = q->rear = -1;
    
    return q;
}

void enqueue(struct queue *q, int c)
{
    if(q->rear == -1)
    {
        q->rear = q->front =0;
        q->data[q->rear] = c;
        q->size++;
    }
    
    else if((q->rear+1) % q->maxsize == q->front)
    {
        printf("QF QSD ");
        int i, size = q->size, front = q->front;
        
        int  temp[size];
        
        for(i=0; i < q->size; i++)
        {
            temp[i] = q->data[front];
            //printf("%d", temp[i] );
            front = (front+1) % q->maxsize;
        }
        
        
        q->data =malloc(sizeof(int) * 2 * q->maxsize);
        q->maxsize = q->maxsize * 2;
        q->front = q->rear = q->size =0;
        
        for(i = 0; i < size; i++)
        {
            q->data[q->rear++] = temp[i];
            q->size++;
        }
        //free(temp);
        //printf("%d  %d", q->maxsize, q->size);
        q->data[q->rear] = c;
        q->size++;
    }
    
    else
    {
        q->rear = (q->rear + 1) % q->maxsize;
        q->data[q->rear] = c;
        q->size++;
    }
}

void display(struct queue *q)
{
    int i, front = q->front;
    for(i = 0; i < q->size; i++)
    {
        printf("-%d-",q->data[front]);
        front = (front+1) % q->maxsize;
    }
    printf("\n");
}

void dequeue(struct queue *q)
{
    if(q->size == 0)
    {
        printf("QE ");
        q->front = q->rear = -1;
    }
    else
    {
        printf("%d ", q->data[q->front]);
        q->front = (q->front +1) % q->maxsize;
        q->size--;
    }
}

void getFront(struct queue *q)
{
    if(q->size == 0)
    {
        printf("QE ");
        q->front = -1;
        q->front =-1;
    }
    else
    {
        printf("%d ", q->data[q->front]);
    }
}

int main()
{
    struct queue *q = createQueue(4);
    int ch = 0, val = 0;
    while(1)
    {
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                scanf("%d", &val);
                enqueue(q,val);
                break;
            case 2:
                dequeue(q);
                break;
            case 3:
                getFront(q);
                break;
            case -1:
                exit(1);
            default:
                break;
        }
    }
    
    return 0;
}

