/*
A linked list can be used to represent a polynomial. Each term in the polynomial has coefficient and exponent.
A polynomial is a sequence of terms. The terms of the polynomial can be stored in a linked list.

Write a C program to compute the product of two polynomials X and Y.

Input/Output Specification:
Input format:
m n p q c1 e1 c2 e2 ......

m: degree of the polynomial X
n: degree of the polynomial Y
p: number of non-zero terms of X
q: number of non-zero terms of Y

followed by (p+q) coefficient and exponents pairs.

- both m and n should be non-negative (>= 0)
- 1 <= p <= m + 1 and 1 <= q <= n+1
- coefficient can be any integer (positive or negative) where as exponent should be non-negative integer (>= 0)
- There should not be duplicate terms in the input, i. e there should not be two terms with same exponent for the same polynomial.
- If there are duplicate terms in the input, it should be treated as invalid input.
- The product should not have duplicate terms.
- If input is invalid you need to display "INVALID INPUT"
- Otherwise display the product of the two polynomials in the format given below.
- Note that terms of the input polynomials are ordered in decreasing order of exponent
- The product of the two polynomials to be displayed in decreasing order of exponent values

Sample Input/Output:
1. (x^2 + 3x + 2) (x^2+1)

Input:2 2 3 2 1 2 3 1 2 0 1 2 1 0
Output: (x^2 + 3x + 2) (x^2 + 1) = (x^4 + 3x^3 + 3x^2 + 3x + 2)


2. (3x^14 + 2x^8 + 1) (8x^14 - 3x^10 + 10x^6)

Input: 14 14 3 3 3 14 2 8 1 0 8 14 -3 10 10 6
Output: (3x^14 + 2x^8 + 1) (8x^14 - 3x^10 + 10x^6) = (24x^28 - 9x^24 + 16x^22 + 30x^20 - 6x^18 + 28x^14 - 3x^10 + 10x^6)

 */


#include <stdio.h>
#include <stdlib.h>

struct node
{
	int coef;
	int expo;
	struct node *next;
};

struct polyFun
{
	struct node *head;
	struct node *tail;
	int degree;
};

struct polyFun *createFun(int degree)
{
	struct polyFun *p = (struct polyFun*)malloc(sizeof(struct polyFun));
	p->head = NULL;
	p->tail = NULL;
	p->degree = degree;
	
	return p;
}


void fill(struct polyFun *p, int c, int e)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->coef = c;
	temp->expo = e;
	temp->next = NULL;
	
	if(p->head ==  NULL)
	{
		p->head = p->tail = temp;
	}
	else
	{
		p->tail->next = temp;
		p->tail = p->tail->next;
	}
	
}
void displayFun(struct polyFun *p)
{
	if(p->head == NULL)
	{
		printf("EMPTY");
		
	}
	struct node *trv;
	trv = p->head;
	while(trv->next !=NULL)
	{
		printf(" %d -- %d ", trv->coef, trv->expo);
		trv= trv->next;
	}
	printf(" %d -- %d \n", trv->coef, trv->expo);
	
}

int flagDuplicateExp(struct polyFun *p, int expo)
{
	//int flag=0;
	if(p->head == NULL)
	{
		return 0;
	}
	struct node *trv;
	trv = p->head;
	while(trv->next !=NULL)
	{
		if(trv->expo == expo)
		{
			return 1;
		}
		trv= trv->next;
	}
	return 0;
}


void multiplyFun(struct polyFun *result, struct polyFun *p1,int p, int q,struct polyFun *p2)
{
	int i=0, x=0, coef, expo;
	struct polyFun *trv;
	struct node *trv1;
	struct node *trv2;
	trv= result;
	trv1=p1->head;
	trv2 = p2->head;
	int loop =0;
	while(1)
	{
		trv2 = p2->head;
		while(1)
		{
			
			coef = trv1->coef * trv2->coef;
			expo = trv1->expo + trv2->expo; 
			//printf("coef %d", coef);
			//printf("expo %d", expo);
			
			struct node *temp = (struct node*)malloc(sizeof(struct node));
			temp->coef = coef;
			temp->expo = expo;
			
			if(trv->head == NULL)
			{
				trv->head = trv->tail = temp;
			}
			else
			{
				trv->tail->next = temp;
				trv->tail = trv->tail->next;
			}
			if(trv2 == p2->tail)
			{
				break;
			}
			trv2 = trv2->next;
			//printf("-- j %d--", j);
		}
		if(trv1 == p1->tail)
			{
				break;
			}
		
		trv1=trv1->next;
		//printf("-- i %d--", i);
	}


}
void sortFun(struct polyFun *result)
{
    struct node *trv1;
	struct node *trv2;
	struct node *trv3;
	int x, flag1=0, flag2=0;
	trv1 = result->head;
	while(1)
	{
	    trv2 = result->head;
	    trv3 = trv2->next;
	    
	    {
	        if(trv2->expo == trv3->expo )
	        {
	            trv2->coef = trv2->coef + trv3->coef;
	            trv2->next = trv3->next;
	            free(trv3);
	            trv1 = result->head;
	            break;
	            
	        }
	        
	        
	        if(trv1 != trv3 && trv1->expo == trv3->expo)
	        {
	         //   printf("2");
	            trv1->coef = trv1->coef + trv3->coef;
	            free(trv3);
	            trv1 = result->head;
	            trv2 = result->head;
	            break;
	            if(trv3 == result->tail)
	            {
	                
	                break;
	            }
	            
                
	            trv2->next = trv3->next;
	        }
	        
	        if(trv2 == result->tail)
			{
		//	    printf("7");
			    flag2=0;
				break;
			}
		//	printf("8");
			flag2++;
			trv2 = trv2->next;
			trv3 = trv3->next;
	    }
	    
	  //  printf("9");
	    if(trv1 == result->tail)
			{
	//		    printf("10");
				break;
			}
	//		printf("11");
		flag1++;
		trv1= trv1->next;
	//	printf("12");
	}
	
	trv2 = result->head;
	   
	while(trv2->next != result->tail)
	{
	     trv3 = trv2->next;
	      if(trv2->expo == trv3->expo )
	        {
	            //printf("--1--");
	            trv2->coef = trv2->coef + trv3->coef;
	            trv2->next = trv3->next;
	            trv3= trv3->next;
	        }
	     
	    if(trv2->expo < trv3->expo)
	        {
	            x = trv2->expo;
	            trv2->expo = trv3->expo;
	            trv3->expo = x;
	            x = trv2->coef;
	            trv2->coef = trv3->coef;
	            trv3->coef = x;
	            trv2 = result->head;
	        }

			trv2 = trv2->next;
	}
}



void display(struct polyFun *p)
{
	if(p->head == NULL)
	{
		printf("EMPTY");
		return;
		
	}
	printf("(");
	struct node *trv;
	trv = p->head;
	while(trv->next !=NULL)
	{
		if(trv->coef == 1 && trv->expo > 1)
		{
			printf("X^%d ", trv->expo);
		}
		else if(trv->expo ==1 && trv->coef > 1)
		{
			printf(" %dX", trv->coef);
		}
		else if(trv->coef == 1 && trv->expo ==1)
		{
			printf(" X ");
		}
		else if(trv->coef !=0 && trv->expo == 0)
			{
				printf("%d",trv->coef);
			}
		else
		{
			printf("%dX^%d ", trv->coef, trv->expo);		
		}
		

		trv= trv->next;
		if(trv->coef>0)
		{
			printf(" + ");
		}

	}
	if(trv->coef == 1)
	{
		if(trv->expo == 0)
			{
				printf(" %d",trv->coef);
			}
		else if(trv->expo == 1)
		    {
		        printf(" 1");
		    }
		
		else
			{
				printf(" X^%d ", trv->expo);
			}
		
	}
	
	else{
		if(trv->expo == 0)
			{
				printf("%d",trv->coef);
			}
		else if(trv->expo == 1)
    	    {
    	        printf(" 1");
    	    }
		else
			{
				printf(" %dX^%d", trv->coef, trv->expo);
			}
	}
	printf(")");
	
}



int main()
{
	int m, n,p ,q,i, cof, expo, flag,count=0;
	scanf("%d",&m);
	scanf("%d", &n);
	if(m<0 || n<0)
	{
		printf("INVALID INPUT");
		return 0;
	}
	scanf("%d", &p);
	scanf("%d", &q);
	
	if((p<1 || p>m+1 ) || (q<1 || q>n+1 ))
	{
		printf("INVALID INPUT");
		return 0;
	}
	struct polyFun *p1 = createFun(m);
	struct polyFun *p2 = createFun(n);
	for (i=0; i<p; i++)
	{
	 //   if (count == p)
	   // {
	     //   printf("INVALID INPUT");
	  //      return 0;
	   // }
	    
		scanf("%d", &cof);
		scanf("%d", &expo);
		if(expo<0)
		{
			printf("INVALID INPUT");
			return 0;
		}
		flag = flagDuplicateExp(p1, expo);
		if(flag==1)
		{
			printf("INVALID INPUT");
			return 0;
		}
		fill(p1,cof,expo);
	//	count++;
	}
    count=0;
	
	for (i=0; i<q; i++)
	{
	   // if (count == q)
	   // {
	   //     printf("INVALID INPUT");
	    //    return 0;
	   // }
	    
		scanf("%d", &cof);
		scanf("%d", &expo);
		if(expo<0)
		{
			printf("INVALID INPUT");
			return 0;
		}
		flag = flagDuplicateExp(p2, expo);
		if(flag==1)
		{
			printf("INVALID INPUT");
			return 0;
		}
		fill(p2,cof,expo);
	//	count++;
	}
	display(p1);
	printf(" ");
	display(p2);
	//printf("\n");
	
	struct polyFun *mul = createFun(p*q);
	multiplyFun(mul, p1,p,q, p2);
	
//	printf(" = ");
//	printf("\n");
//	display(mul);
	sortFun(mul);
	printf(" = ");
	display(mul);

	return 0;
}


