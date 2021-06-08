/*An m X n matrix is said to have a saddle point if there is an element a[i][j] of the array such that a[i][j] is the smallest value in ith row and largest value in jth column. Write a modularized C program that displays the location of the saddle point. If the matrix has more than one saddle point display the first location of the saddle point starting from row 0 and column 0 (elements are visited from left to right and row by row). Remember array index starts from 0.

Note: Array elements can be both positive or negative integers.

For example, for the following 3 X 3 matrix element a[2][0] (7) is a saddle point
1 2 3
4 5 6
7 8 9

Where as the following 3 X 4 matrix does not have a saddle point.
1 2 3 4
5 6 7 8
10 11 12 6

The following matrix has more than one saddle points (a[2][0] and a[2][1])
1 2
3 4
5 5
Input/Output Specification:
- Your program should read the dimension of the matrix and followed by the elements of the matrix.
- Display -1 if the matrix does not have a saddle point.
- Display the row and column indices of the first saddle point.
- matrix dimensions should be > 0, otherwise display -2
Sample Input/Output:
Input:
3 3
1 2 3
4 5 6
7 8 9
Output
2 0

Input:
3 3
1 2 3
4 5 6
9 8 5
Output:
-1

Input:
1 3
3 4 1
Output:
0 2

Input:
3 2
1 2
3 4
5 5
Output:
2 0

Input:
0 4
Output:-2 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int row, column , i , j, k, element, min_row=0, col_pos=0, row_pos=0, max_col=0, flag=-1;
    scanf("%d", &row);
    scanf("%d", &column);
    
    if(row <= 0 || column <= 0)
    {
        printf("-2");
        exit(1);
    }
    
    int *matrix = (int*)malloc(sizeof(int)*row);
    for(i = 0; i < row; i++)
    {
        int *matrix = (int*)malloc(sizeof(int)*column);
    }
    
    for(i=0;i<row;i++)
    {
        for(j = 0; j < column; j++)
        {
            scanf("%d", &element);
            *(matrix + i*column +j) = element;
        }
    }
    /*for(i=0 ; i<row; i++)
    {
        for(j=0; j<column;j++)
        {
            printf("%d", *(matrix + i*column +j));
        }
        printf("\n \n");
    }*/
    
    
    for(i = 0; i < row; i++)
    {
        min_row = *(matrix + i*column + 0);
        row_pos = i;
        
        for(j=0; j < column; j++)
        {
            if(min_row > *(matrix + i * column + j))
            {
                min_row = *(matrix + i * column +j);
                col_pos = j;
            }
        }
        
        max_col = min_row;
        //printf("--%d-- \n ",col_pos);
        for(k = 0; k < row; k++)
        {
            //printf("---");
            if(max_col < *(matrix + k * column + col_pos))
            {
                flag = -1;
                //printf("++");
                break;
            }
            else
            {
                flag = 1;
            }
            //printf("%d",k);
        }
        
        if(flag == 1)break;
    }
    
    if(flag == 1)
    {
        printf("%d %d", row_pos,col_pos);
        //printf("%d", col_pos);
    }
    else
    {
        printf("%d", flag);
    }
    free(matrix);
    return 0;
    
}

