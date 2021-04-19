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