/*
Write a simple application to conduct a computer based quiz. The quiz consists of questions with answers true or false only. Suppose the questions are present in a text file Questions.txt, in the following format:

First line of the file consists of the number of questions present in the file and the rest of the file consists of the question followed by answer in separate lines. Your program should display questions one by one, and prompt the user to enter his answer, at the end display the score of the user. And also display the questions the user has wrongly answered along with the correct answer. (You can assume that each question is of length at most 80 characters). Use command line arguments to provide the text file to the program.

A sample Questions.txt file:
3
There are one thousand years in a CENTURY.
False
DOZEN is equivalent to 20.
False
The past tense of FIND is FOUND.
True
 */


#include <stdio.h>
#include <stdlib.h>

struct node{
	int qNo;
	int ans;
	int inputAns;
	struct node *next;
};

struct cbq
{
	struct node *head;
	struct node *tail;
};

struct cbq *createDB()
{
	struct cbq *db = (struct cbq*)malloc(sizeof(struct cbq));
	db->head = NULL;
	db->tail = NULL;
}

int inputAns()
{
	int temp;// flag=0;
	
	while(1)
	{
		printf("\nEnter 1 if Answer is True or 0 for False:");
		scanf("%d", &temp);
		if(temp ==1 || temp == 0 )
		{
			break;
		}
		else
		{
			printf("\nINVALID INPUT\n");
		}
	}
	
	return temp;
}

int Ans(char x)
{
	if(x == 'F' || x == 'f')
	{
		return 0;
		
	}
	else if(x == 'T' || x == 't')
	{
		return 1;
	}
	else
	{
		printf("File Error");
		return 2;
	}
}

void fillDB(struct cbq *db, int count,int inputans , int Ans)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->qNo = count;
	temp->ans = Ans;
	temp->inputAns = inputans;
	temp->next = NULL;
	
	if(db->head == NULL)
	{
		db->head = db->tail = temp;
	}
	else
	{
		db->tail->next = temp;
		db->tail = db->tail->next;
	}
}

int calScore(struct cbq *db, FILE *eval)
{
	int score = 0,flag, qNo=0,i;
	
	struct node *temp = db->head;
	char x;
	for(flag=0;flag < db->tail->qNo;flag++)
	{
		if(temp->ans == temp->inputAns)
		{
			score = score + 1;
		}
		else
		{
			qNo = temp->qNo;
			while((x= fgetc(eval)) != '\n'); //skips 1st line
			for(i=1;i<qNo; i++)
			{
				while((x= fgetc(eval)) != '\n'); //skips questions till wrongly answered question is reached
				while((x= fgetc(eval)) != '\n'); //skipsanswer
					
			}
			printf("Question no %d: ", qNo);
			while( (x= fgetc(eval)) != '\n') // reads wrongly answered Question
			{
				printf("%c", x);
			
			}
			printf("\nCorrect Answer: ");
			while( (x= fgetc(eval)) != '\n') // reads Answer
			{
				if(x == EOF)
				{
					break;
				}
				printf("%c", x);
				
			}
			printf("\n");
			fseek(eval, 0, SEEK_SET);
			
		}
		if(temp->next == NULL)
		{
			break;
		}
		temp = temp->next;
	}
	return score;
}

void freeDb(struct cbq *db)
{
	if(db->head == NULL)
	{
		printf("EMPTY");
	}
	else
	{
		struct node *temp;
		while(db->head != db->tail)
		{
			temp=db->head;
			db->head = db->head->next;
			free(temp);
		}
		temp=db->head;
		free(temp);
		db->head = db->tail =NULL;	
	}
}

int main(int argc, char** argv)
{
	char x;
	int noOfQuestions=0, count=0, temp,inputans, answer, score, flag=0;
	if(argc >1)
	{
		printf("filename: %s \n", *(argv+1));
	}
	else
	{
		puts("filename was not given");
		return 0;
	}
	FILE *input=fopen(*(argv+1),"r");
	struct cbq *db = createDB();
	
	if(input==0)
	{
		printf("could not open file");
	}
	else
	{
		while((x= fgetc(input)) != '\n') // reads first line
		{
			noOfQuestions = noOfQuestions *10+(x - '0');
		}
		printf("No Of Questions: %d \n",noOfQuestions);
		
		while( (x= fgetc(input)) != EOF ) 
		{
			printf("\nQuestion no :%d \n", ++count);
			
			while( x != '\n') // reads Question
			{
				printf("%c", x);
				x= fgetc(input);
			}
			inputans = inputAns(); //inputs ans
		
			x= fgetc(input);
			answer = Ans(x);
			
			while((x= fgetc(input)) != '\n')
			{
				if(x == EOF)
				{
					break;
				}
			}
			
			fillDB(db, count,inputans, answer);
			printf("\n");	
			
		}
		printf("\nTest Finished calulating score...  \n");
		FILE *eval = fopen(*(argv+1),"r");
		if(eval==0)
		{
			printf("could not open file");
		}
		else
		{
			score = calScore(db, eval);
			fclose(eval);
		}
		printf("\nyour score is: %d out of %d questions \n", score, noOfQuestions);
		
		freeDb(db);
		free(db);
	}

	
	
	fclose(input);
	return 0;
}
