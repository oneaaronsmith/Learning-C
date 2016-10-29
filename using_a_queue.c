/*Aaron M. Smith
 Introduces working with a queue.*/ 

//**********Libraries**********************
#include <stdio.h>
#include <stdlib.h>

//**********Definitions********************

typedef struct node_ { 
	int data;
	struct node_* next;
} Node;

//**********PROTOTYPES*********************
 
Node* enqueue(Node* front, int data);
int dequeue(Node** frontPtr);
void freeQueue(Node* front);
void printQueue(Node* front);
Node* filterEven(Node* head);

//**********MAIN****************************

int main(void) {
	Node* queue = NULL;
	
	//Initialize choice and number variables
	int i;
	int choice = 0;
	
	//Give options
	printf("Enter 1 to Enqueue\nEnter 2 to Dequeue\nEnter 3 to Quit\n");
	
	//Run options until user wants to quit
	while(choice != 3)
	{
		//Scan choice
		printf(">");
		scanf("%d",&choice);
		while(choice > 3 || choice < 1)
		{
			printf("Invalid Option. Please try again: ");
			scanf("%d",&choice);
		}
		
		//Set up switch cases to handle choices
		switch(choice)
		{
			//Enqueue Option
			case 1:
			{
				//Ask the user for his/her number
				printf("Enter a number to enqueue: ");
				scanf("%d",&i);
				
				//Add them to your list of dates and print result (turned down?)
				queue = enqueue(queue,i);
				printQueue(queue);
				break;
				
			}
			
			//Dequeue option
			case 2:
			{
				if(queue == NULL)
				{
					printf("Queue is already empty\n");
					break;
				}
				//Initialize Node** to hold front of queue
				Node** frontPtr;
				frontPtr = &queue;
				
				//Initialize int to keep track of what was removed and call function
				int removed;
				removed = dequeue(frontPtr);
				
				//Print results
				printf("%d was dequeued\n",removed);
				printQueue(queue);
				break;
				
			}
			
			//Quit Option
			case 3:
			{
				if(queue == NULL)
				{
					printf("Goodbye\n");
					break;
				}
				//Call the filter function.
				printf("Filtered:\n");
				filterEven(queue);
				
				//Print the results
				printQueue(queue);
				
				//Call the free function to free all of the queue
				freeQueue(queue);
				
				//After break, while loop will stop.
				break;
			}
		}
	}
	
	return 0;
}


//**********FUNCTIONS**********//

Node* enqueue(Node* front, int data) { //This function places an int on the end of the queue. FINALIZED
	
	//Initialize utility pointers.
	Node* previous;
	Node* current;
	Node* new;
	
	//Introduce the new node:
	new = malloc(sizeof(Node));
	
	//Only proceed if the new node is not NULL
	if(new != NULL)
	{
		//Let the new node hold your data
		new->data = data;
		new->next = NULL;
		
		//Set current to the beginning
		previous = NULL;
		current = front;
		
		//Allow previous to be placed at the final node.
		while(current != NULL)
		{
			previous = current;
			current = current->next;
		}
		
		//If previous is NULL, this is the first node in the queue.
		if(previous == NULL)
		{
			front = new; //Let the front pointer be pointing to the only node.
		}
		else //if a node exists, add the new node to the end of the list.
		{
			previous->next = new; //put the new node on the end
			new->next = current;  //set the new node's next pointer as NULL.
		}
	}
	else //If malloc fails:
	{
		printf("Sorry, but your data could not be stored. No memory available.");
	}
	
	//Return the beginning of the list
	return front;
}

int dequeue(Node** frontPtr) //Removes a node from beginning of the queue. FINALIZED
{
	//Initialize utility pointers.
	Node* current;
	Node* temp;
	
	//Set current at the beginning
	current = *frontPtr;
	
	//Initialize removal int, and give it the number that is being removed.
	int removal;
	removal = current->data;
	
	//Move the current ptr to the next node
	current = current->next;
	
	//Perform actual removal of the front node and free the node.
	temp = *frontPtr;
	*frontPtr = current;
	free(temp);
	
	//Return the integer that was removed.
	return removal;
}
	
void printQueue(Node* front) //Print your queue data. FINALIZED.
{
	//Initialize utility pointer and set it at the beginning.
	Node* current;
	current = front;
	
	//If the start pointer is null, there is nothing to print
	if(front == NULL)
	{
		printf("Queue is empty.\n");
	}
	else
	{	
		//while loop moves through the list while printing
		while(current != NULL)
		{
			printf("%d--> ",current->data);
			current = current->next;
		}
		
		//Print null at the end
		printf("NULL\n");
	}
}


void freeQueue(Node* front) //Free all nodes in the queue. CHECKED, FINALIZED.
{
	//Initialize utility pointers.
	Node* current;
	Node* temp;
	
	//Set current at the front.
	current = front;
	
	//This while loop should leave a wake of freedom by freeing all nodes until there are none left.
	while(current != NULL)
	{
		temp = current; 			//Set temp to current to hold on to that node.
		current = current->next;	//Move current over by one node
		free(temp);					//Free the node after moving.
	}
}

Node* filterEven(Node* front) //Hold on to your hat, this one filtered all even numbers out of the queue. FINALIZED
{
	//Initialize utility pointers.
	Node* previous;
	Node* current;
	Node* temp;
	
	//Set current to the front;
	current = front;
	
	//If current->next is NULL, the base case is triggered. If current->next is NULL, the function ends.
	if(current->next == NULL)
	{
		return current; //Return current and start the recursive train
	}
	else
	{
		//Let previous be called current, then move current over one.
		previous = current;
		current = current->next;
		
		//If current's data is even, let previous->next skip over to current->next, and then free current.
		if(current->data % 2 == 0)
			{
				temp = current;
				previous->next = current->next;
				free(temp);
			}
		
		//Call the function on itself to continue recursively
		filterEven(current);
	}
	
	//Return front.
	return front;
	
}
