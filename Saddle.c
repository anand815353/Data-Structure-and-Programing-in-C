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

