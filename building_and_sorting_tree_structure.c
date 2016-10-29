/*Aaron M. Smith
  Purpose: Introduce tree data structures. Building balanced trees*/

/*****LIBRARIES****/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*****DEFINITIONS*****/
typedef struct node_ {
	int data;
	struct node_* left;
	struct node_* right;
} Node;

/*****PROTOTYPES*****/
Node* buildBalancedTree(int array[], int low, int high);
void printTree(Node* root, int depth);
void padding(int depth);
void freeTree(Node* root);
void quicksort(int array[],int low,int high);
void sort(int array[],int low, int high);
void preorder(Node* root);
void inorder(Node* root);
void postorder(Node* root);
int height(Node* root);

/*****MAIN*****/
int main(int argc, char* argv[]) {
	
	srand( time(NULL)); //Use this so that rand will give new numbers
	int array[10]; 		//Initialize array of a size 10 
	int i; 				//Initialize a counter
	
	//The following lines give the array random values and prints them for the user.
	printf("\nThe random numbers are: ");
	for(i = 0; i < 10 ; i++)
	{
		array[i] = rand() % 50;
		printf("%d ",array[i]);
	}
	
	//Now, call the sort function and print the sorted information
	quicksort(array,0,9);
	
	printf("\nAfter the sort, the array is: ");
	for(i = 0; i < 10; i++)
	{
		printf("%d ",array[i]);
	}
	
	//Now actually build the balanced tree:
	Node* root = buildBalancedTree(array, 0, 9);
	
	//Find and print the height of the tree
	int rootdepth;
	rootdepth = height(root);
	printf("\nThe height of the tree is: %d",rootdepth);
	
	//Print the binary tree in a number of ways: pre, in, and post-order
	printf("\nPre-order: ");
	preorder(root);
	
	printf("\nIn-order: ");
	inorder(root);
	
	printf("\nPost-order: ");
	postorder(root);
	
	//Print the tree for fancifulness. (this is from the prelab)
	printf("From the prelab, the tree looks like this:\n\n");
	printTree(root, 0);
	
	//Free the tree and wave goodbye.
	freeTree(root);
	
	return 0;
}

/*****FUNCTIONS*****/

void quicksort(int array[],int low, int high)
{	
	//Make a pivot point for initial sorting.
		int pivot = low;
		
	//Keep track of the beginning and end.
	int lowside = low;		
	int highside = high;
		
	if(low >= high)
		return;
	else
	{
		//Quick sort makes an initial pass on the array to make sure the greater numbers are on the right.
		while(low < high) //we will be moving both sides of the array near eachother until they reach the middle.
		{
			while(array[low] < array[pivot] && low < high) //as long as the left is less than the midpoint, keep moving ->.
			{
				low = low+1; //move the index up
			}
			while(array[high] > array[pivot]) //as long as the right is greater than the midpoint, keep moving <-
			{
				high = high-1; //move the index down.
			}
			if(low < high)
			{
				//After the movements, it may be necessary to switch the numbers these sides are on.
				int temp = array[pivot];
				array[pivot] = array[high];
				array[high] = temp;
			}
		}
	}
	
	int temp = array[pivot];
	array[pivot] = array[high];
	array[high] = temp;
	
	//After all of the drama has unfolded, we can call the function on itself for recursion sake.
	quicksort(array,lowside,high-1);
	quicksort(array,high+1,highside);
	
}

void sort(int array[], int low, int high) //This is an insertion sort. It is purposed with sorting if I can't finish quicksort.
{
	int i,j,temp;
	for(i = 1; i <= high; i++)
	{
		j = i;
		while(j > low && array[j] < array[j-1]) //Moves a smaller integer back in line on the array
		{
				temp = array[j]; 			//the swap
				array[j] = array[j-1];		//the swap
				array[j-1] = temp;			//the swap
				j--;
		}
	}
}

void preorder(Node* root) //This function prints the tree in preorder style
{
	if(root == NULL)
		return;
	else
	{
		printf("%d ",root->data); //top, preorder
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(Node* root) //This function prints the tree in inorder style
{
	if(root == NULL)
		return;
	else
	{
		inorder(root->left);
		printf("%d ",root->data); //middle, inorder
		inorder(root->right);
	}
}
	
void postorder(Node* root) //This function prints the tree in postorder style
{
	if(root == NULL)
		return;
	else
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data); //bottom, postorder (This is the way to free later)
	}
}

int height(Node* root) //This function finds the maximum depth of the tree
{
	if(root == NULL)
		return 0;
	else
	{
		//Find the height of the left side by moving as far possible left
		int leftheight = height(root->left);
		
		//Find the height of the right side by moving as far possible right
		int rightheight = height(root->right);
		
		/*The function will start to recursively add up the lengths as they return.
		  There may be a case in which the right side is greater than the left. This should work for
		  either case.*/
		  
		if(leftheight > rightheight)
		{
			return leftheight + 1; //At the start, 
		}
		else if(rightheight >= leftheight)
		{
			return rightheight + 1;
		}
	}
	
	return 0; //Default case
}

Node* buildBalancedTree(int array[],int low, int high)
{
	/*This function is purposed for building a balanced binary search tree. The function takes in a sorted array
	  and index identifiers for the beginning and end of the array (lowest and highest index). It uses the index
	  identifiers to make a root at the middle of the array, and then recursively do the same for the left and
	  right sides of the tree. Due to the recursive nature, function needs to stop when low becomes greater than 
	  high*/
	
	Node* root; //Initialize node pointer.
	
	if(low <= high) //If the tree reaches the end of a side, it will not insert a new part.
	{
	
		//Begin by finding information on the middle of the array.
		int middle = (low+high)/2; 		//finds middle of the array.
		int datapoint = array[middle]; 	//gets the number for the node data
		
		//Next, malloc space for the new node and input data
		root = malloc(sizeof(Node));
		if(root == NULL)
		{	
			printf("Failed to malloc space for node");
			return NULL;
		}
		else
		{
			root->data = datapoint; //sets datapoint in the node
			root->right = NULL;		//sets right to NULL
			root->left = NULL;		//sets left to NULL
		}
		
		//the right side of the tree recursively builds off of the right half of the array
		root->right = buildBalancedTree(array,middle+1,high);
		
		//the left side of the tree recursively builds off of the left half of the array
		root->left = buildBalancedTree(array,low,middle-1);
	}
	else
	{
		return NULL; //Base case to end recursion.
	}
	return root;
}

void freeTree(Node* root)
{
	/*This function is meant to free the binary search tree. It takes in the root of the tree and moves as far
	  forward as it can. As long as it can keep moving, it goes throughout the whole tree and frees the leaves
	  recursively. It only deletes leaves because they both return NULL.*/
	  
	if(root == NULL)
	{
		return;
	}
	else
	{
		freeTree(root->left); 	//Tree proceeds to the end of the leftmost leaf of the tree
		freeTree(root->right);	//After left pushes back, check the right. If there is anything to the right, it will move.
		free(root);				//Free this leaf and move back recursively, scorching the earth as you pass.
	}
}
		
void printTree(Node* root, int depth) { 
	if (root == NULL) {
		padding(depth);
		printf("~\n");
	} else {
		printTree(root->right, depth + 1);
		padding(depth);
		printf("%d\n", root->data);
		printTree(root->left, depth + 1);
	}
}

void padding(int depth) {				
	int i;
	for (i = 0; i < depth; i++) {
		putchar('\t');
	}
}

