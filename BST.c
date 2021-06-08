/*
Implement the following C functions related to Binary Search Tree (BST)

-Insert(BST, e) : insert element e into BST

-Delete(BST, e): delete element e from the BST

-LookUp(BST, e): search if element e is present in the BST. Returns 1 for success and 0 for failure.

-GetHight(BST): returns the height of the BST

-PrintSorted(BST): Displays the elements of the BST in non-decreasing order. (In-order traversal)

 

Now write a menu driven test function main() to test the functions of BST.

1 e : insert element e into the BST

2 e: delete element e from the BST

3 e: check is element is there in the bst

4: display the hight of the tree

5: print element of the BST in ascending order

-1: exit

 

Sample Input/Output:

input=1 50 1 30 1 20 1 40 1 70 1 80 1 60 5 4 3 40 3 90 2 20 2 30 2 50 2 80 4 3 20 3 60 5 -1
output=20 30 40 50 60 70 80 2 1 0 1 0 1 40 60 70 */


#include <stdio.h>
#include <stdlib.h>

struct node 
{
	int data;
	struct node *left;
	struct node *right;
};

struct BST
{
	struct node *root;
	int count;
};

struct BST *createBST()
{
	struct BST *bst = (struct BST*)malloc(sizeof(struct BST));
	bst->root = NULL;
	bst->count= 0;
	
	return bst;
}

struct node *createNode(int data)
{
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

void searchPosition(struct node *root, struct node *newNode)
{
	if((newNode->data > root->data))
	{
	//	printf("%d ->", root->data);
		if (root->right != NULL)
		{
			searchPosition(root->right, newNode);
		}
		else if (root->right == NULL)
		{
			root->right = newNode;
		}
		else
		{
			printf("right EXCEPTION");
		}
		
	}
	if((newNode->data < root->data))
	{
	//	printf("%d ->", root->data);
		if (root->left != NULL)
		{
			searchPosition(root->left, newNode);
		}
		else if (root->left == NULL)
		{
			root->left = newNode;
		}
		else
		{
			printf("left EXCEPTION");
		}
		
	}
}



void insert(struct BST *bst, int val)
{
	struct node *newNode = createNode(val);
	if(bst->root == NULL)
	{
		bst->root = newNode;
		bst->count = 1;
	}
	else
	{
		bst->count++;
		searchPosition(bst->root, newNode);
	}
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

void dispalyTree(struct node *root)
{

	printf(" %d", root->data);
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

struct node *minNode(struct node *root)
{
	/*if(root->left != NULL)
		return minNode(root->left);
	else*/
	while(root && root->left != NULL)
	    root = root->left;
	return root;
}

struct node *delete(struct node *root, int val)
{
	if(root == NULL)
	{
		return NULL;
	}
	else
	{
		if(val < root->data)
		{
			root->left = delete(root->left, val);
		}
		else if(val > root->data)
		{
			root->right = delete(root->right, val);
		}
		else
		{
			if(root->left == NULL && root->right == NULL) // no child node
			{
				root= NULL;
			}
			
		    else if(root->left == NULL) // has only 1 left child
			{
				struct node *temp = root->right;
				//root = root->left;
				free(root);
				return temp;
			}
			
			else if(root->right == NULL) // has only 1 right child
			{
				struct node *temp = root->left;
				//root = root->right;
				free(root);
				return temp;
			}
			
			else // has both child
			{
				struct node *temp = minNode(root->right);
				
				root->data = temp->data;
				root->right = delete(root->right, temp->data);
			}
		}
		
		return root;
	}
	
}

int main()
{
	struct BST *bst = createBST();
	int ch = 0, val = 0;
	while(1)
	{
		scanf("%d", &ch);
		if(ch == -1)
		{
			free(bst);
			return 0;
		}
		switch(ch)
		{
			case 1: 				//insert
				scanf("%d", &val);
				insert(bst, val);
				break;
			case 2: 				//delete
				scanf("%d", &val);
				bst->root = delete(bst->root, val);
				break;
			case 3: 				//check element present or not
				scanf("%d", &val);
				printf("%d ", lookUP(bst->root, val));
				break;
			case 4: 				//display height of tree
				printf("%d ", getHeight(bst->root)-1);
				break;	
			case 5: 				//PrintSorted..In-order
				displayInorder(bst->root);
				break;
			/*case 6:					// No of elemnts in tree
				 printf("\n count %d \n", bst->count);
				 break;
			case 7:					//display tree not sorted
				dispalyTree(bst->root);
				break;*/
			default:
				break;
		}
	}
	
	
	
	return 0;
}

