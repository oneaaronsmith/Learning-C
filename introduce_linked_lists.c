/*Aaron M. Smith
  Working with linked lists.*/

//*****LIBRARIES*****
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//*****DEFINITIONS*****
#define assert_with_msg(expression, msg) { \
	if (!(expression)) { \
		printf("\x1b[31m%s", msg);\
		assert(expression);\
	}\
}

typedef struct node_ {
	int data;
	struct node_* next;
} Node;

//*****PROTOTYPES*****
Node* build_list(const char* filename);

void print_list(Node* head);

void reverse_list(Node* head);

void multiply_by(Node* head, int val);

void free_list(Node* head);

 //*****START MAIN*****
int main( int argc, char *argv[]) 
{
	if(argc != 2)
	{
	printf("\nInsufficient arguments at command line\n");
	return 0;
	}

	//Calls your build_list function
	Node* head = build_list(argv[1]);
	
	print_list(head);
	
	//Node* newhead = reverse_list(head);
	
	int multiple;
	
	//Read in number user would like to multiply by
	printf("Enter a number to multiply by: ");
	scanf("%d",&multiple);
	
	//Multiply list by the number
	multiply_by(head,multiple);
	
	//Print the multiplied list
	print_list(head);
	
	//print reversed list
	print_list(head);
	
	//Free the list
	free_list(head);

	return 0;
}

Node* build_list(const char* filename) {
	
	Node* startPtr = NULL; //leading pointer for list
	Node* newPtr = NULL; 		//pointer to a new node
	Node* previousPtr = NULL;	//pointer to a previous node
	Node* currentPtr = NULL; 	//pointer to a current node
	
	//Open file for reading, if it fails send error and exit
	FILE* fp = fopen(filename,"r");
	if(fp == NULL)
	{
		printf("\nError, could not open input file %s\n",filename);
		return NULL;
	}
	
	//Since it is unknown how long file is, set while with !feof
	int number;
	while(!feof(fp))
	{
		// 1) Scan the file for the data value
		fscanf(fp,"%d",&number);
		
		//Check for feof again. If this wasn't here, the while loop would run once more than necessary.
		//if(feof(fp))
			//break; IF THERE IS A NEW LINE IN THE INPUT FILE REMOVE "//" A SECOND CHECK IS NECESSARY
		
		// 2) malloc space for the newest pointer
		newPtr = malloc(sizeof( Node )); //malloc space to create a node
		
		// 3) If the malloc is successful put the data into the newPtr. Fail if NULL
		if(newPtr != NULL)
		{
			newPtr->data = number; 	//places scanned number in struct
			newPtr->next = NULL;	//initialize struct's self referential pointer to NULL
			
			previousPtr = NULL;		//Set previous pointer as null
			currentPtr = startPtr;	//start at the beginning of the list
			
			//If there is no previous pointer, set a start (first case), 
			if(currentPtr == NULL)
			{
				startPtr = newPtr;
			}
			else //If there is, set the new pointer as the head and move the original head
			{
				startPtr = newPtr;
				startPtr->next = currentPtr;
			}
		}
		else
		{
			printf("%c not inserted. No memory\n",number); //If malloc failed, give the information
		}
	}
	
	//Close file and return the pointer
	fclose(fp);
	return startPtr;
	
}

//Based on chapter 12 notes, prints the linked list
void print_list(Node* head)
{
	//If the start pointer is null, there is nothing to print
	if(head == NULL)
	{
		printf("No list, sorry\n");
	}
	else
	{
		
		//while loop moves through the list while printing
		while(head != NULL)
		{
			printf("%d--> ",head->data);
			head = head->next;
		}
		
		printf("NULL\n\n");
	}
}

void multiply_by(Node* head, int val) //this function multiplies each list part
{
	//Initialize pointers
	Node* currentPtr;
	
	currentPtr = head;
	//Go through the list while multiplying
	while(currentPtr != NULL)
	{
		currentPtr->data *= val;
		currentPtr = currentPtr->next;
	}
	
	return;
}

void free_list(Node* head) //this function frees the list
{
	//Initialize the needed pointers
	Node* previousPtr;
	Node* currentPtr = head;
	
	//Go through the list while freeing
	while(currentPtr != NULL)
	{
		previousPtr = currentPtr;
		currentPtr = currentPtr->next;
		free(previousPtr);
	}
}
