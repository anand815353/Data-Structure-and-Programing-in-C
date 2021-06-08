/* Write an efficient and scallable implementation of dynamically growing Circular Queue using Arrays.

The Circular queue should have the following features:
1. The queue is to hold integer elements.
2. Intial maximum size of the queue to be 4 elements.
3. Everytime the queue is full the queue size to be doubled using dynamic memory allocation.
4. It should have the following functions
    - createQueue() - Dynamically create queue
    -enqueue(Q, e) - inserts element e into the queue
    -dequeue(Q) - Removes and retruns element from the queue using FIFO machanism
    -getFront(Q) - returns the element at the front, element will not be removed from the queue
    
5. If dequeue(Q) or getFront(Q) is called when queue is empty, then print the message "QE"
6. If enqueue(Q, e) is called when queue is full for the current limit, print the message "QF QSD" and then double the queue size and insert the element e into the queue.

Once you implement the Circular Queue function, write a menu driven main() test function to test functions of the queue.
The test function acts based on the user inputs. Inputs would be as follows:
1 x - enqueue intreger x onto the queue
2   - dequeue the queue and print the element removed from the queue
3   - print the front element of the queue
-1  - stop

Sample Input: 1 10 1 200 1 40 1 80 1 17 2 2 2 2 2 2 1 20 1 30 1 2 1 -12 1 -200 1 30 1 50 1 70 1 80 -1
Output: QF QSD 10 200 40 80 17 QE QF QSD



Input:2 3 1 11 1 -1 1 1 1 111 1 1111 3 2 3 2 3 2 3 2 3 2 3 2 -1

Output: QE QE QF QSD 11 11 -1 -1 1 1 111 111 1111 1111 QE QE */



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

