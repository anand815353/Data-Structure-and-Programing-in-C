/* importing header files */

#include <stdio.h>  
#include <math.h>

/* main function begins here */

int main() 
{
	int n,i,flag=0;  //variable declaration 
					 // flag=0 by default to catch if no entered is 1 which is not prime

	scanf("%d",&n);  // taking input variable and storing

	if(n<=0)         //checks if no is negative or zero
	{
		flag=-1;     // flags -1 if entered no is less than 1  
	}
	
	else if(n==2)    //checks if no is equal to 2  
	{
		flag=1;		// flag 1 if entered no is 2 
	}
	
	else			// else block for all other positive nos
	{
		for(i = 2; i <= ceil(sqrt(n)); i++)  //for loop to loop though all the nos beteen 2 and sqrt of that no.
											 //ceilng value of sqrt to catch 3 which is 1.732 and is less than 2, loop would have ended without checking prime.  
		{
			if(n % i == 0)     // checks any no is divisible between 2 and n
			{
				flag=0;       // flags 0 for non prime nos
				break;
			}
			else
			{
				flag = 1;   // flags 1 for prime nos
			}			
		}
	}				
	printf("%d",flag);   //outputs result
		
	return 0;
}
