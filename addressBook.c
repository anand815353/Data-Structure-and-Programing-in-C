/* 
Create student address management application in C (Address Book) using C Random
access file processing. Usually a record in a student address book contains the following fields:
Roll Number, Name, Phone Number and Email

The application should contain the following options:
-Adding new student record (Append at the end of the file)
-Modifying student record (based on roll number)
-Search of student address based on name
-Deleting student record (If the Roll Number is “#DELETE#” then the record should be treated as deleted).

When the program loads initially all the records marked
“#DELETE#” should permanently removed from the file by creating a new student.dat
file which contains only active records.
The data stored in the file (file name: student.dat) should be permanent until the user deletes himself using the delete option of the application.
Note: Go through the C file opening modes and use the proper mode to open the address data file in order to make sure the data is never lost.

The following function can be used to rename a file in C:
int rename(const char *old_filename, const char *new_filename)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentRec
{
    char rollNo[100];
    char firstName[100];
    char lastName[100];
    char email[100];
    char phNo[20];
};

void appendRecord(char* filename)
{
	struct StudentRec s;
	printf("Enter the roll Number: ");
	scanf("%s", s.rollNo);
	printf("Enter First name: ");
	scanf("%s", s.firstName);
	printf("Enter Last name: ");
	scanf("%s", s.lastName);
	printf("Enter email: ");
	scanf("%s", s.email);
	printf("Enter phone number: ");
	scanf("%s", s.phNo);
	
	
	FILE *fptr = fopen(filename, "ab+");
    if(fptr == NULL)
    {
		printf("\nFILE ERROR!\n");
		exit(0);
    }
    else
    {
    	fwrite(&s, sizeof(struct StudentRec), 1, fptr);
    	printf("\nRecord added sucessfully!");
	}
	
	fclose(fptr);
}

void display(char* filename)
{
	printf("\n");
	FILE *fptr = fopen(filename, "rb");
    if(fptr == NULL)
    {
		printf("\nFILE ERROR!\n");
		exit(0);
    }
	while(!feof(fptr))
    {
		struct StudentRec s;
		if(fread(&s, sizeof(struct StudentRec), 1, fptr))
		{
		    printf("%s, %s, %s, %s, %s\n", s.firstName, s.lastName, s.rollNo, s.email, s.phNo);
		}
    }
    fclose(fptr);
}

void searchRecord(char* filename)
{
	FILE *fptr = fopen(filename, "rb");
	if(fptr == NULL)
    {
		printf("\nFILE ERROR!\n");
		exit(0);
    }
    char firstName[200];
    char lastName[100];
    printf("Enter First name: ");
	scanf("%s", &firstName);
	
	printf("Enter Last name: ");
	scanf("%s", &lastName);
	
	int flag=0;
    
	while(!feof(fptr))
    {
		struct StudentRec s;
		if(fread(&s, sizeof(struct StudentRec), 1, fptr))
		{ 
		    if((strcmp(firstName,s.firstName)==0) && (strcmp(lastName,s.lastName)==0))
		    {
		    	if(strcmp("#DELETE#",s.rollNo)==0)
			    {
			    	printf("\nThis Record is Deleted\n");
				}
				else
				{
					printf("Record Found: %s, %s, %s, %s, %s\n", s.firstName, s.lastName, s.rollNo, s.email, s.phNo);
				}
		    	flag=1;
		    	break;
			}
		}
    }
    fclose(fptr);
    if(flag == 0)
    {
    	printf("\nRecord Not Found\n");
	}
}

void modifyRecord(char* filename)
{
	FILE *fptr = fopen(filename, "rb+");
	if(fptr == NULL)
    {
		printf("\nFILE ERROR!\n");
		exit(0);
    }
    char rollNo[100];
    printf("Enter Roll no: ");
	scanf("%s", &rollNo);

	int flag=0,record=0;
	struct StudentRec temp;
	while(!feof(fptr))
    {
		struct StudentRec s;
		if(fread(&s, sizeof(struct StudentRec), 1, fptr))
		{ 
		    if(strcmp(rollNo,s.rollNo)==0)
		    {
		    	
		    	printf("Enter new roll Number: ");
				scanf("%s", temp.rollNo);
				printf("Enter First name: ");
				scanf("%s", temp.firstName);
				printf("Enter Last name: ");
				scanf("%s", temp.lastName);
				printf("Enter email eg: ");
				scanf("%s", temp.email);
				printf("Enter phone number: ");
				scanf("%s", temp.phNo);
				
		    	fseek(fptr,sizeof(struct StudentRec)*record,SEEK_SET);  //
              	fwrite(&temp,sizeof(struct StudentRec),1,fptr);
              	printf("\nRecord Modified sucessfully\n");
		    	
		    	flag=1;
		    	break;
			}
			record++;
		}
    }
    fclose(fptr);
    if(flag == 0)
    {
    	printf("\nRecord Not Found\n");
	}	
}

void deleteRecord(char* filename)
{
	FILE *fptr = fopen(filename, "rb+");
	if(fptr == NULL)
    {
		printf("\nFILE ERROR!\n");
		exit(0);
    }
    char rollNo[100];
    printf("Enter Roll no: ");
	scanf("%s", &rollNo);

	int flag=0,record=0;
	
	while(!feof(fptr))
    {
		struct StudentRec s;
		if(fread(&s, sizeof(struct StudentRec), 1, fptr))
		{ 
		    if(strcmp(rollNo,s.rollNo)==0)
		    {
		    	strcpy(s.rollNo,"#DELETE#");
				fseek(fptr,sizeof(struct StudentRec)*record,SEEK_SET);  //
              	fwrite(&s,sizeof(struct StudentRec),1,fptr);
		    	printf("\nRecord Deleted sucessfully!\n");
		    	flag=1;
		    	break;
			}
			record++;
		}
    }
    fclose(fptr);
    if(flag == 0)
    {
    	printf("\nRecord Not Found\n");
	}	
}

void del(char* filename)
{
	FILE *fptr = fopen(filename, "rb");
	if(fptr == NULL)
    {
		printf("\nFILE ERROR!\n");
		exit(0);
    }
    FILE *temp =fopen("temp.dat","ab+");
    
	if(temp == NULL)
    {
		printf("\nFILE ERROR!\n");
		exit(0);
    }
    
    int flag=0;
	while(!feof(fptr))
    {
		struct StudentRec s;
		if(fread(&s, sizeof(struct StudentRec), 1, fptr))
		{ 
		    if(strcmp("#DELETE#",s.rollNo)==0)
		    {
		    	//do nothing
			}
			else
			{
				fwrite(&s, sizeof(struct StudentRec), 1, temp);
			}
		}
    }
    fclose(temp);
    fclose(fptr);
    remove("student.dat");
    
    int value; 
    value = rename("temp.dat", "student.dat"); 
    if(rename("temp.dat", "student.dat") != 0) 
    { 
    	remove("temp.dat");
        printf("\nApp Ready!\n"); 
    } 
    else
    { 
        printf("\nFILE ERROR!\n"); 
    }
    
}

int main(int argc, char** argv)
{
	char* filename;
	if(argc >1)
	{
		filename = *(argv+1); //if file name is given though command line argument
	}
	else
	{
		filename="student.dat"; //else file name is assigned
	}
	//printf("%s", filename);
	FILE *input=fopen(filename,"r");
	
	if(input==0)
	{
		FILE *input=fopen(filename,"w"); // if file is not present it creates a file. 
		
	}
	else
	{
		printf("\nFile Present\n");
	}
	
	fclose(input);
	del(filename);
	
	int ch;
	while(1)
	{
		printf("\nchoice: 1.add record; 2.Modify record; 3.search student; 4.delete Record; 5.display all_records; -1.exit: ");
		scanf("%d", &ch);
		if(ch == -1)
		{
			return 0;
		}
		switch(ch)
		{
			case 1:appendRecord(filename);
				break;
			case 2:modifyRecord(filename);
				break;
			case 3:searchRecord(filename);
				break;
			case 4: deleteRecord(filename);
				break;
			case 5:display(filename);
				break; 
			default:
				break;
		}
		
	}
	return 0;
}
