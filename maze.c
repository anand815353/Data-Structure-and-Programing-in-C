/*
The following is a two-dimensional character array of size 12X12 which represents a maze.
The symbol ‘#’ represent a wall of the maze and the symbol ‘.’ represents a possible path.
There is an entry point and exit point of the maze, which are denoted by a ‘.’ In the first
column and 12th column respectively. Write a C program which takes text file which contains
the maze as command line argument and prints the minimum number of moves required to
go from entry to exit. If there is no path from entry to exit display “-1”.
You need to formulate the maze as a graph and use Breadth First Search to find shortest path
from entry to exit. You can treat each cell as a vertex and if we can go from one cell to other
cell with one move add edge between the corresponding vertices.
For example, for the below maze:
############
...##.##...#
##........##
#..######.##
####.......#
#....#.###.#
###........#
#...######.#
#####...#..#
#...#.#.#.##
#.#...#.....
############
Minimum number of moves required is: 22
Test cases attached should have the following output:
ptestcase1 : 22, ptestcase2 : 11, ptestcase3 : 19, ntestcase4 : -1
 */



#include <stdio.h>
#include <stdlib.h>

#define SIZE 12
#define maxNode 144

//////////////////////////////////////////////////////////////////
//Queue related operations

struct qNode
{
    int data;
	struct qNode *next;
};

struct Queue			
{
	struct qNode *front;			
	struct qNode *rear;			
};

struct Queue* createQueue()
{
    struct Queue *q;
    q = (struct Queue *) malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    
    return q;
}

void enqueue(struct Queue *q, int c)
{
	struct qNode *temp;
	temp = (struct qNode *) malloc(sizeof(struct qNode));
	temp->data = c;
	temp->next = NULL;
    if(isEmpty(q) == 0) //not empty
    {
        q->rear->next = temp;
        q->rear=q->rear->next;
    }
    else
    {
       q->front = temp;
       q->rear = temp;
       
    }
}

void display(struct Queue *q)
{
    struct qNode *temp;
    temp = q->front;
    while(temp->next!=NULL)
    {
        printf("-%d-",temp->data);
        temp=temp->next;
    
    }
    printf("\n");
}

int dequeue(struct Queue *q)
{
	int val=0;
	struct qNode *temp;
	if(isEmpty(q) == 1) 
	{
		q->front = NULL;
		q->rear = NULL;
	}
    if(isEmpty(q) == 0)
    {
    	val = q->front->data;
    	temp = q->front;
    	q->front = q->front->next;
    	free(temp);

    }
    return val;
}

int isEmpty(struct Queue *q)
{
	if(q->front == NULL)
	{
		return 1;
	}
	return 0;
	
}

/////////////////////////////////////////////////////////////////
/// Adjacency List related operations

typedef struct adjNode
{
	int n;
	struct adjNode* next;
} Node;

typedef struct adjList
{
	struct adjNode *head;
} List;

List *adjList[maxNode] ={0};

List createList()
{
	int i;
	for(i=0; i<maxNode;i++)
	{
		adjList[i] = (List *)malloc(sizeof(List));
		adjList[i]->head =NULL;
	}
}

void addNode(int s, int d)
{
	Node *dest, *temp, *src;
	dest = (Node *)malloc(sizeof(Node));
	dest->n =d;
	dest->next = NULL;
	
	if(adjList[s]->head == NULL)
	{
		adjList[s]->head =dest;
	}
	else
	{
		temp = adjList[s]->head;
		while(temp->next !=NULL)
		{
			temp  =temp->next;
		}
		temp->next = dest;
	}

	
}

void createAdjList(int maze[][SIZE])
{
	createList();
	int i=0,j=0,source,destination,vertex=0;
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			
			if(maze[i][j]>0)
			{
				source=vertex++;
				if(maze[i][j-1] >0)//left
				{
					destination= source-1;
					addNode(maze[i][j],maze[i][j-1]);
				}
				if(maze[i][j+1] >0)//right
				{
					destination= source+1;
					addNode(maze[i][j],maze[i][j+1]);
				}
				if(maze[i-1][j] >0)//up
				{
					destination= source-SIZE;
					addNode(maze[i][j],maze[i-1][j]);
				}
				if(maze[i+1][j] >0)//down
				{
					destination= source+SIZE;
					addNode(maze[i][j],maze[i+1][j]);
				}
			}
		}
	}	
}


void printAdjList()
{
	int i;
	for(i=0; i<maxNode; i++)
	{
		if(adjList[i]->head != NULL)
		{
			Node *p = adjList[i]->head;
			printf(" node %d ->",i);
			
			while(p)
			{
				
				printf(" %d ", p->n);
				p=p->next;
			}
			printf("\n");
		}
		
		
	}
}

void freeAdjList()
{
	int i;
	for(i=0; i<maxNode; i++)
	{
		if(adjList[i]->head != NULL)
		{
			Node *p = adjList[i]->head;
			Node *temp;
			
			while(p)
			{
				
				temp= p;
				p=p->next;
				free(temp);
			}
		}
		free(adjList[i]);	
	}
	
}



/////////////////////////////////////////////////////////////////
// BFS related operations

int findStart(int maze[][SIZE])
{
	int i=0,j=0;
	for(i=0;i<SIZE;i++)
	{
		if(maze[i][0] >0)
		{
			break;	
		}
	}
	return maze[i][0];
}

int findEnd(int maze[][SIZE])
{
	int i=0,j=0;
	for(i=0;i<SIZE;i++)
	{
		if(maze[i][SIZE-1]>0)
		{
			break;
		}
	}
	return maze[i][SIZE-1];
}

int bfs(int parent[],int start, int end, int count)
{
	int visited[count]; //count = no of existing node 
	
	int i;
	for(i=0;i<count;i++)
	{
		visited[i] = 0;
		parent[i] = 0;
	}
	
	Node* temp = adjList[start]->head;
	struct Queue *q = createQueue();
	enqueue(q,start);

	int prnt =  start;
	visited[start] = 1;
	parent[start] = -1; //  -1  represents start
	//printf(" %d - ", start);
	
	temp=temp->next;
	int countvisit=1;
	while(countvisit<count-1)
	{
		
		while(temp)//traverse adjacent nodes in adjList
		{
			 
			if(visited[temp->n] == 0)
			{
				countvisit++;
				enqueue(q, temp->n); //insert in q
				visited[temp->n] = 1;
				parent[temp->n] = prnt;
			}
			temp = temp->next;
			
		}
		if(q->front == NULL)
		{
			break;
		}
		
		prnt = dequeue(q);
		temp = adjList[prnt]->head;
	}
	/*for(i=0;i<count;i++)
	{
		printf(" %d visited %d \n",i, visited[i] );
	};
	for(i=0;i<count;i++)
	{
		printf("node %d parent %d\n", i, parent[i] );
	};*/
	
	int countpath=0,trvrs;
	trvrs = end;
	
	while(parent[trvrs] !=-1)
	{
		countpath++;
		trvrs = parent[trvrs];
		if(parent[trvrs]==0)
		{
			countpath = -1;
			break;
			
		}
	}
	free(q);
	return countpath;
}

void printpath(int parent[], int end, int steps)
{
	int countpath=0,trvrs,i,j;
	trvrs = end;
	int path[steps];
	path[i++] = end;
	while(parent[trvrs] !=-1)
	{
		countpath++;
		path[i++] =  parent[trvrs];
		trvrs = parent[trvrs];
		if(parent[trvrs]==0)
		{
			countpath = -1;
			break;
		}
	}
	while(i >1 )
	{
		printf("%d->", path[--i]);
	}
	printf("%d", path[--i]);
	printf("\n");
	
}

void printmaze(int maze[][SIZE])
{
	
	int i,j;
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			if(maze[i][j] <10)
			{
				printf("  %d   ",maze[i][j]);
			}
			else
			{
				printf("  %d  ",maze[i][j]);
			}
			
		}
		printf("\n");
	}
}



int main(int argc, char** argv) 
{
	
	if(argc >1)
	{
		printf("filename: %s \n", *(argv+1));
	}
	else
	{
		puts("filename was not given");
		return 0;
	}
	
	int maze[SIZE][SIZE];
	FILE *input=fopen(*(argv+1),"r");
	int row=SIZE,col=SIZE;
	int i=0,j=0;
	int count = 1;
	
	if(input==0)
	{
		printf("could not open file");
		return 0;
	}
	else
	{
		
		char x;
		while((x=fgetc(input)) != EOF ) 
		{
			if(x =='.')
			{
				maze[i][j] = count++;
				j++;
			}
			else if(x =='#')
			{
				maze[i][j] = 0;
				j++;
			}
			else if(x== '\n')
			{
				j=0;
				i++;	
			}
			else if(x==EOF)
			{
				break;
			}	
		}
		fclose(input);
	}
	
	createAdjList(maze);
	int start = findStart(maze);
	int end = findEnd(maze);

	int parent[count];
	int steps = bfs(parent,start, end, count);
	printf("\n Minimum No. of Steps : %d", steps);
	int ch;
	while(1)
	{
		
		printf("\n\n1. print adjacency list; 2 print maze; 3. print path; -1. EXIT : ");
		scanf("%d", &ch);
		if(ch == -1)
		{
			freeAdjList();
			return 0;
		}
		switch(ch)
		{
			case 1: printAdjList();
				break;
			case 2: printmaze(maze);
				break;
			case 3:
				if(steps==-1)
				{
					printf("path doesnot exist");
				}
				else
				{
					printpath(parent, end, steps);
				}
				break;
			default:
				break;
			
		}
	}
	
	
	return 0;
}







