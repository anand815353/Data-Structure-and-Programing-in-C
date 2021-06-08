/*
Write a C program to sort an array of n integer elements using Heap sort.

Your implementation should have the following function to process Max-Heap.

-MAX-HEAPIFY()

-BUILD-MAX-HEAP()

-HEAP-SORT()

The following optional functions can also be implemented.

-MAX-HEAP-INSERT()

-HEAP-EXCTRACT-MAX()

-HEAP-INCREASE-KEY()

-HEAP-MAXIMUM()

Sample Input/Output: Number of numbers followed by the actual numbers

Input: 6 21 13 56 44 102 12

Output: 12 13 21 44 56 102

Input:0
Output: INVALID INPUT
 */

#include <stdio.h>
#include <stdlib.h>

struct heap 
{
	int maxSize;
	int arr[];
};

struct heap* createHeap(int max)
{
	int i;
	struct heap *h = (struct heap*)malloc(sizeof(struct heap*) +sizeof(int)*max);
	h->maxSize = max;
	return h;
}


void fill(struct heap *h, int pos, int val)
{
	h->arr[pos] = val;
}

void swap( int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void MAX_HEAPIFY( struct heap* h, int count, int i)
{
	int max = i;
	int leftChild = 2*i+1;
	int rightChild = 2*i+2;
	
	if(leftChild < count && h->arr[leftChild] > h->arr[max])
	{
		max = leftChild;
	}
	
	if(rightChild < count && h->arr[rightChild] > h->arr[max])
	{
		max = rightChild;
	}
	
	if(max != i)
	{
		swap(&h->arr[i], &h->arr[max]);
		MAX_HEAPIFY(h,count, max);
	}
}

void BUILD_MAX_HEAP(struct heap* h)
{
    int i, count = h->maxSize;
	for(i =  (count / 2) -1; i>=0;i-- )
	{
		MAX_HEAPIFY(h , count, i);
	}
}

void HEAPSORT(struct heap* h)
{
    BUILD_MAX_HEAP(h);
    
	int i, count = h->maxSize;
	for(i = count - 1; i>=0; i--)
	{
		swap(&h->arr[0], &h->arr[i]);
		MAX_HEAPIFY(h, i , 0);
	}
	
}



void display(struct heap* h)
{
	int *temp;
	temp = h->arr;
	int i;
	for(i=0;i < h->maxSize; i++)
	{
		printf("%d ", temp[i]);
	}
	printf("\n");
}

int main()
{
	int a, i, val;
	scanf("%d", &a);
	if(a < 1)
	{
		printf("INVALID INPUT");
		return 0;
	}
	struct heap *h = createHeap(a);
	for(i=0;i<a; i++)
	{
		scanf("%d", &val);
		fill(h, i, val);
	}
	
	//display(h);
	HEAPSORT(h);
	//printf("sorted");
	display(h);
	
	
	return 0;
}
