#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX];
//int arr[MAX][MAX];

void dfs(int adj[][100], int vertices_count,int v, int* visited)
{
	int j;
	visited[v] = 1;
	for(j=0;j<vertices_count;j++)
	{
		if(adj[v][j] == 1 && visited[j] == 0)
			dfs(adj, vertices_count, j, visited);
	}
}

void count_comp(int arr[][2],int vertices_count, int edge_count)
{
	int i,j,  visited[vertices_count];
	for(i=0;i<vertices_count;i++)
	{
		for(j=0;j<vertices_count;j++)
		{
			adj[i][j] = 0;
		}
		visited[i] = 0;
	}
	
	for(i=1; i<edge_count;i++)
	{
		adj[arr[i][0] -1][arr[i][1] -1] =1;
		adj[arr[i][1] -1][arr[i][0] -1] =1;
	}
	
	int connected_components = 0;
	for(i=0;i<vertices_count;i++)
	{
		if(visited[i]==0)
		{
			dfs(adj, vertices_count, i, visited);
			connected_components++;
		}
	}
	printf("No of connected components: %d", connected_components);
	
}

int main(int argc, char** argv) 
{
	int vertices_count=0, edge_count=0, temp=0, flag;
	flag=0;
	int i=0,j=0;
	
	if(argc >1)
	{
		printf("filename: %s \n", *(argv+1));
	}
	else
	{
		puts("filename was not given");
		return 0;
	}
	FILE *input =fopen(*(argv+1),"r");
	
	if(input==0)
	{
		printf("could not open file");
		return 0;
	}
	else
	{
		int x;
		while((x= fgetc(input)) != '\n') // reads first line
		{
			if(x == ' ')
			{
				flag=1;
			}
			if (flag==0)
			{
				vertices_count = vertices_count *10+(x - '0');
			}
			
			if(flag==1 && x !=' ')
			{
				edge_count = edge_count*10 + (x - '0');
			}
		}
		printf("vertices_count: %d, ", vertices_count);
		printf("edge_count: %d \n", edge_count);
		int arr[edge_count][2];
		flag=0;
		i=0;
		int val =0;
		while((x= fgetc(input)) != EOF)
		{
			if(x == ' ')
			{
				flag = 1;
			}
			else if(x == '\n')
			{
				i++;
				flag=0;
			}
			else
			{
				val = val* 10 + (x - '0');
			}
			
			if(val >vertices_count || val<=0) //check valididity of edge
			{
				printf("INVALID EDGE %d", val);
				return 0;
			}  
			
			
			if(x ==' ')
			{
				
				arr[i][0] = val;
				val=0;
			}
			else if(x!=' ' && x == '\n')
			{
				arr[i-1][1] = val;
				val=0;
			}
			arr[i][1] = val;
			
		}
		fclose(input);
		count_comp(arr,vertices_count, edge_count);
			
		
	}
	
	
	return 0;
}
