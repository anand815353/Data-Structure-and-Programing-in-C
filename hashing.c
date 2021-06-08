/* The aim of this exercise is to remove duplicate strings from the attached file (emailList.txt) using a hash table.
You can assume that the size of the final set of strings is less than 100.

Implement a hash table using open addressing to resolve collisions. Internally you should use a fixed sized array as a hash table to store strings.
When there are collisions use open addressing scheme to resolve the collisions.
To get hash code, you need to convert a string to an integer;
Choose a suitable way to do this and when collision occurs, compare the strings to detect duplicates.

The input file name and the output file name will be provided as command line arguments.
Your program should read strings from input file and output (strings after removing duplicates) should be written to the output file. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

int main(int argc, char** argv) {
	if(argc >1)
	{
		printf("filename: %s \n", *(argv+1));
	}
	else
	{
		puts("filename was not given");
		return 0;
	}
	FILE *input = fopen(*(argv+1),"r");

	char* hashTable[MAX];
	int i;
	for(i = 0; i < MAX; i++) 
		hashTable[i] = '\0';

	char email[MAX];
	int temp,hash;

	while(fscanf(input, "%s", email) != EOF) 
	{
		temp = 0;
		i=0;
		while(email[i] != '\0')
		{
			temp += (int)email[i];
			i++;
		}

		hash = temp % 100;

		while((hashTable[hash] != '\0') &&  (strcmp(hashTable[hash], email) !=0) ) 
		{
			hash = (hash + 1) % MAX;	
		}

		hashTable[hash] = (char*)malloc(sizeof(char) * MAX);
		strcpy(hashTable[hash], email);
	}
	
	input = freopen(*(argv+1), "w", stdout);
	for(i = 0; i < 100; i++) 
	{
		if(hashTable[i]!='\0')
		{
			fprintf(input,"%s\n", hashTable[i]);
		}		
	}

	fclose(input);
	return 0;
	
}
