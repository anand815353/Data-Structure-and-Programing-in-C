#include <stdio.h>
#include <stdlib.h>

struct node 
{
	int data;
	struct node *left;
	struct node *right;
	int height;
};

struct AVL
{
	struct node *root;
	int count;
};

struct AVL *createAVL()
{
	struct AVL *avl = (struct AVL*)malloc(sizeof(struct AVL));
	avl->root = NULL;
	avl->count= 0;
	
	return avl;
}

struct node *createNode(int data)
{
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 1;
	
	return newNode;
}

void dispalyTree(struct node *root)
{

	printf(" %d", root->data);
	printf("(_%d)", root->height);
	if(root->left == NULL)
	{
		printf(" left-end");
	}
	if(root->right == NULL)
	{
		printf(" right-end");
	}
	if(root->left != NULL)
	{
		printf(" left ->");
		dispalyTree(root->left);
	}
	if(root->right != NULL)
	{
		printf(" right ->");
		dispalyTree(root->right);
	}
}


int getHeight(struct node *root)
{
	if(root == NULL)
		return 0;
	else
	{
		int leftHeight = getHeight(root->left);
		int rightHeight = getHeight(root->right);
		
		return	(leftHeight > rightHeight) ? leftHeight+1 : rightHeight+1;
	}
}

int findBalanceFactor(struct node *temp)
{
	if(temp == NULL)
		return 0;
	return (getHeight(temp->left) - getHeight(temp->right));
}

struct node *right_Rotate(struct node *temp)
{
	struct node *temp1 = temp->left;
	struct node *temp2 = temp1->right;
	
	temp1->right = temp;
	temp->left = temp2;
	
	temp->height = getHeight(temp);
	temp1->height = getHeight(temp1);
	
	return temp1;
}

struct node *left_Rotate(struct node *temp)
{
	struct node *temp1 = temp->right;
	struct node *temp2 = temp1->left;
	
	temp1->left = temp;
	temp->right = temp2;
	
	temp->height = getHeight(temp);
	temp1->height = getHeight(temp1);
	
	return temp1;
}

struct node *insert(struct node *root, int val)
{
	if(root == NULL)
		return createNode(val);
	
	if(val < root->data)
		root->left  = insert(root->left, val);
	else if(val > root->data)
		root->right = insert(root->right, val);
	else
		return root;
	
	root->height = getHeight(root);
	
	int balance_factor = findBalanceFactor(root);
	
	if(balance_factor > 1 && val < root->left->data)
	{
		return right_Rotate(root);
	}
	if(balance_factor < -1 && val > root->right->data)
	{
		return left_Rotate(root);
	} 
	if(balance_factor > 1 && val > root->left->data )
	{
		root->left = left_Rotate(root->left);
		return (right_Rotate(root));
	}
	if(balance_factor < -1 && val < root->right->data)
	{
		root->right = right_Rotate(root->right);
		return left_Rotate(root);
	}
	return root;
}

void displayInorder(struct node *root)
{
	if( root == NULL )
	{
		printf("EMPTY");
		return;
	}
	else
	{
		if(root->left !=NULL)
		{
			displayInorder(root->left);
			
		}
		printf("%d ", root->data);
		if(root->right !=NULL)
		{
			displayInorder(root->right);
		}
	}
	
}

int lookUP(struct node *root, int val)
{
	int flag = 0;
	if (root->data == val)
	{
		return flag = 1;
	}
	if((root->left !=NULL) && ( val < root->data))
	{
		flag = lookUP(root->left, val);
		if (flag ==1)
		{
			return flag;
		}
	}
	if((root->right != NULL) && (val > root->data))
	{
		flag =  lookUP(root->right, val);
		if (flag ==1)
		{
			return flag;
		}
	}
	return flag;
}

struct node *minNode(struct node *root)
{
	while(root && root->left != NULL)
	    root = root->left;
	return root;
}

struct node *delete(struct node *root, int val)
{
	if (root == NULL)
		return root;

	if (val < root->data)
	    root->left = delete(root->left, val);
	
	else if (val > root->data)
	    root->right = delete(root->right, val);
	
	else
	{
	    if ((root->left == NULL) || (root->right == NULL))
		{
			struct node *temp = root->left ? root->left : root->right;
			if (temp == NULL)
			{
				temp = root;
	        	root = NULL;
	        }
			else
			{
				*root = *temp;
			}
	        free(temp);
	    }
		else
		{
			struct node *temp = minNode(root->right);
			root->data = temp->data;
			root->right = delete(root->right, temp->data);
	    }
	}
	
	if (root == NULL)
	{
	    return root;
	}
	    
	root->height = getHeight(root);
	int balance_factor = findBalanceFactor(root);
	if (balance_factor > 1 && findBalanceFactor(root->left) >= 0)
	{
		return right_Rotate(root);
	}
	if (balance_factor > 1 && findBalanceFactor(root->left) < 0)
	{
	    root->left = left_Rotate(root->left);
	    return right_Rotate(root);
	}
	
	if (balance_factor < -1 && findBalanceFactor(root->right) <= 0)
	{
		return left_Rotate(root);
	}
	
	if (balance_factor < -1 && findBalanceFactor(root->right) > 0)
	{
	    root->right = right_Rotate(root->right);
	    return left_Rotate(root);
	}
	return root;
}


int main() 
{
	struct AVL *avl = createAVL();
	int ch = 0, val = 0;
	while(1)
	{
		scanf("%d", &ch);
		if(ch == -1)
		{
			free(avl);
			return 0;
		}
		switch(ch)
		{
			case 1: 				//insert
				scanf("%d", &val);
				avl->root = insert(avl->root, val);
				avl->count++;
				break;
			case 2: 				//delete
				scanf("%d", &val);
				avl->root = delete(avl->root, val);
				avl->count--;
				break;
			case 3: 				//check element present or not
				scanf("%d", &val);
				printf("%d ", lookUP(avl->root, val));
				break;
			case 4: 				//display height of tree
				printf("%d ", getHeight(avl->root)-1);
				break;	
			case 5: 				//PrintSorted..In-order
				displayInorder(avl->root);
				break;
			/*case 6:					// No of elemnts in tree
				 printf("\n count %d \n", avl->count);
				 break;
			case 7:					//display tree not sorted
				dispalyTree(avl->root);
				break;*/
			default:
				break;
		}
	}
	
	
	return 0;
}