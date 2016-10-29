/*Aaron M. Smith
  Description: This assignment will be used to read bank account information including the name, account number, and amount in the account. 
  The data will  be loaded from a text  file in a 2D character array, integer array, and a float array. 
  Multiple functions will be done on the information and an output file will give that information.
  
  Loading and processing data from a file.
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //For strcpy only. Cannot use strcmp

/********************FUNCTION PROTOTYPEs******************************/ 
int load_data(char*, char**,int*, float*, int);
void print_data(char**,int*,float*,int);
void report(char**,float*,int*,int);
int check_account(char**,int*,char*,int,int);
int string_compare(char*,char*);
int highest_amount(float *,int);
int lowest_amount(float *,int);
float average_amount(float *,int);
void write_data(char*,char**,int*,float*,int,int,int,float);
void sort_data(char**,int*,float*,int);

/******************************MAIN**********************************/

int main(int argc, char **argv)
{
	if(argc != 4) //Programs needs a certain amount of inputs. 
	{
		printf("\nInsufficient arguments \n"); //If amount of inputs is insufficient, an error message is displayed and the program ends.
		return 0;
	}

	int s = atoi(argv[2]); //s for size, converts command line input to an integer

	int *acn,useracn;   //Initializes a pointer for the account number and variables
	float *amt; 		//Initializes a pointer and variable for the amount of money in the account
	char **name; 		//Initializes a double pointer for the name of the account holder

	acn = malloc(sizeof(int)*s);				//Allocates space to the account number pointer
	amt = malloc(sizeof(float)*s);				//Allocates space to the amount pointer
	name = malloc(sizeof(char*)*s);  			//Allocates space to the name double pointer
	char *username = malloc(sizeof(char)*s);	//Allocates space to a pointer for later use

	//There exist multiple characters inside the character string. The following code will allocate space for the account holder name:
	int i;
	for(i = 0; i < s; i++)
	{
		*(name+i) = malloc(sizeof(char)*100); 		//Characters receive allocation space
	}

	int status = load_data(argv[1],name,acn,amt,s); //Calls the load_data function to load data from .txt file  into the created pointers

	if(status==0) //If opening unsuccessful, the following  error will be displayed
	{
		printf("\n Unable to open the input file \n");
		return 0;
	}
	
	print_data(name,acn,amt,s); //Calls print_data function to print pointer information

	//Now that the data has been loaded and printed, the program prompts user to make a user selection:

	printf("\nEnter a name: ");
	scanf("%s",username);
	
	printf("\nEnter an account number: ");
	scanf("%d",&useracn);

	//The user's choices must be valid. The program will check to see if they are available and will return the index for which they were found.

	int location = 0;

	location = check_account(name,acn,username,useracn,s); //Sends information to check_account function.

	if(location == -1)
	{
		printf("\nThe user does not have a bank account.\n"); //If the check_account function determines the user does not exist, error message is displayed.
		report(name,amt,acn,s);								  //Prints a report of the accounts for old times sake
		return 0;
	}

	//The program will then prompt the user to make an action selection:
	
	int choice = 0;
	float amount = -1;

	while(choice < 1 || choice > 2) //There are only two selections.
	{
	printf("\nDo you want to\n1. Withdraw\n2. Deposit\nSelection: "); //Displays menu
	scanf("%d",&choice);

	if(choice < 1 || choice > 2)
		printf("\nInvalid choice. Please try again.\n");
	}

	printf("\nEnter the amount: "); //Prompts user to make a selection
	scanf("%f",&amount);
	
	switch(choice) //2 Scenarios
	{
		case 1:
		if(amount > *(amt+location))
		{
			printf("\nNot enough money in your account to make that transaction.\n");
			report(name,amt,acn,s);
			return 0;
		}
		else
			*(amt+location) = *(amt+location) - amount; //If there is enough, the amount taken is taken from the amount in the account.
		break;

		case 2:
		if(amount > 0) 								    //cannot withdraw negative money
			*(amt+location) = *(amt+location) + amount; //Adds money deposited
		break;
	}

	/*The program decides to make everyone feel good about themselves by telling them who has the most money, the least, and what their accounts
	  would look like in a socialist society. */
	
	int rich,poor; //Integers to hold the index of our wonderful friends.
	float socialist;
	
	rich = highest_amount(amt,s); 		//Sent to find the index of the richest person

	poor = lowest_amount(amt,s);  		//Finds the index of the poorest person

	socialist = average_amount(amt,s);  //Averages everyone's accounts

	report(name,amt,acn,s); 			//Prints a report for the user to marvel at

	/*The final part of this program places the account information and report into an output file and frees the memory.*/

	write_data(argv[3],name,acn,amt,s,rich,poor,socialist); //Calls write_data to write information to output.txt
	
	sort_data(name,acn,amt,s);	//Sorts data alphabetically

	printf("\n\nBONUS: Sort information alphabetically\n");

	print_data(name,acn,amt,s); //prints data after sorting.

	free(acn); //FREEEEDOMM
	free(amt);
	free(username);
	free(name);

	//FIN


return 0;
}

int load_data(char* filename, char **name, int *x, float *y, int size)
{
	/*Comments on load_data: load data takes the input file name, character 2d array, integer array, float array, and size. It opens an 
	  input file and returns 0 if opening is unsuccessful. Otherwise, it loads the account information from the .txt file and returns 1.*/
	

	int i = 0; //Creates a counter for the allocating of data.

	FILE* file = fopen(filename,"r"); //opens the command prompt .txt file for reading

	if(file == NULL) //If the file is not successfully opened, it will return NULL. And the function will return 0.
	{
		return 0; 	 //Ends function
	}

	int id; 	//Account number
	float amt;  //Amount of money in account
	char *n = malloc(sizeof(char)*100); //allocates space for the names of the account holders to be read.

	for(i = 0; i < size ; i++) 			//Data is gathered from the .txt file and stored in the pointer arrays.
	{
		fscanf(file,"%s %d %f",n,&id,&amt);

		strcpy(*(name+i),n); //Names are assigned
		*(x+i) = id;		 //Ids are assigned
		*(y+i) = amt;		 //Money amounts are assigned.
	}

	fclose(file); //Closes file.
	return 1;
}

void print_data(char **name, int *act, float *amt, int size)
{
	//This function prints the pointer information as loaded in the main (load_data)

	printf("\n%-10s%-13s%-13s\n","Name","Account Number","  Amount"); //Prints headers

	int i = 0;

	for( i = 0; i < size; i++)
	{
		printf("%-10s %-13d %-13.2f\n",*(name+i),*(act+i),*(amt+i)); //Prints all of the available data.
	}
}

int check_account(char **name, int *acn, char *username, int useracn, int size)
{
	/*This function takes the 2D character name array, account number, name the user gave, account the user gave, and size. 
	  It searches for the given account number and name and returns the index if it is found. Otherwise it returns -1.*/

	int i;
	int nameindex  = 0; 	//Will be used to compare index
	int acnindex   =-1;	//Will also be used to compare index. The indexes have separate defaults.
	int comparison = 0; 	//Default is that the usernames are not equal
	int result     =-1;	//Default is set for the account numbers being inequal

	for(i = 0; i < size ; i++)
	{
		comparison = string_compare(*(name+i),username);	//Calls string_compare function to see if strings are equivalent

		if(comparison == 1)	//If strings are equivalent, ends function after saving the index information
		{ 
			nameindex = i;
			break;
		}
	}
		if(comparison == 0)	//If there were not equal, the function ends
			return -1;

	for(i = 0; i < size; i++)
	{
		if(useracn == *(acn+i))
		{
			acnindex = i; //If there is a match for username and account number, the index is returned and the program ends.
		}
	}

	if(nameindex == acnindex) //If the index information matches, the function sends the index location.
		return nameindex;
	else
		return -1;
}

int string_compare(char *string1,char *string2)
{
	//Note, the strings might not be the same size!
	
	int status = 0; //Will be changed to 1 if the strings are equivalent.
	int i = 0;
	
	while( *(string1+i) != '\0' || *(string2+i) != '\0')
	{
		if(*(string1+i) != *(string2+i)) //Compares strings
			return 0;
		i++;
	}

	return 1;
}

int highest_amount(float *amt,int size) //finds the index for the account with the greatest value of $
{
	int i; 		//Almighty counter
	int j = 0;  //A marker to remember the greatest one.
	
	for(i = 0; i < size-1; i++)
	{
		
		if(*(amt+j) < *(amt+i)) //if the j index is lower than the i index it is changed to the j index
			j = i;
	}

	return j;
}

int lowest_amount(float *amt,int size)
{
	//This function finds the index for the account which has the lowest balance
	
	int i; 		//The counter returns as fortold by fate
	int j = 0;  //Alas, the marker returns as well to rembereth whence he was lowly.

	
	for(i = 0; i < size-1 ; i++)
	{
		if(*(amt+j) > *(amt+i)) //if the j index is higher than the i index, it is changed to the i index
			j = i;
	}

	return j;
}

float average_amount(float *amt,int size)
{
	//This function finds the average of all money in the accounts
	
	int i; 			 //Counter
	float total = 0; //Retains the total of the account money
	float average;   //Averages the account money

	for(i = 0; i < size ; i++)
	{
		total += *(amt+i);
	}
	
	average = total/size;

	return average; //Returns average
}

void report(char **name,float *amt,int *acn,int s)
{
	/*This function prints a report of the rich, poor, and average*/

	int rich = highest_amount(amt,s); //finds high index

	int poor = lowest_amount(amt,s);  //finds low index

	float socialist = average_amount(amt,s); //finds average

	printf("\n%s has the highest amount at $%.2f in account number %d\n",*(name+rich),*(amt+rich),*(acn+rich));	
	printf("%s has the lowest amount at $%.2f in account number %d\n",*(name+poor),*(amt+poor),*(acn+poor));
	printf("The average amount is $%.2f\n",socialist);
}

void write_data(char *filename, char **name, int *acn, float *amt, int size, int rich, int poor, float socialist)
{
	/*Comments on write_data: write data takes the output file name, character 2d array, integer array, float array, size, highest index, lowest index, and average.
	  It opens an output file and returns 0 if opening is unsuccessful. Otherwise, it writes the account information into the output.txt file.*/
	

	int i = 0; //Creates a counter for the allocating of data.

	FILE *file = fopen(filename,"w"); //opens the command prompt .txt file for reading

	if(file == NULL) //If the file is not successfully opened, it will return NULL. And the function will return 0.
	{
		printf("Error: File did not open.");
	}
	
	
	fprintf(file,"\n%-10s%-13s%-13s\n","Name","Account Number","  Amount"); //Prints headers (same as print function)
	for( i = 0; i < size; i++)
	{	
		fprintf(file,"%-10s %-13d %-13.2f\n",*(name+i),*(acn+i),*(amt+i)); //Prints all of the available data.
	}
	
	fprintf(file,"\n%s has the highest amount at $%.2f in account number %d\n",*(name+rich),*(amt+rich),*(acn+rich));	
	fprintf(file,"%s has the lowest amount at $%.2f in account number %d\n",*(name+poor),*(amt+poor),*(acn+poor));
	fprintf(file,"The average amount is $%.2f\n",socialist);

	fclose(file); //Closes file.
}

void sort_data(char **name, int *acn, float *amt, int size) //This function sorts the data alphabetically. Strcmp is allowed for the bonus.
{
	/*This function sorts data alphabetically*/

	int    i; 										//creates a counter
	int    pass;									//creates a pass
	int    cp;										//creates a comparison integer
	char  *hold1 = malloc(sizeof(char)*size+1);		//creates a hold for names
	int   *hold2 = malloc(sizeof(int)*size+1);		//creates a hold for account numbers
	float *hold3 = malloc(sizeof(float)*size+1);		//creates a hold for amount of money

	for(pass = 1; pass < size; pass++) //The data is sorted by bubble sort
	{
		for(i = 0; i < size-1; i++)
		{
			cp = strcmp(*(name+i),*(name+i+1));
			if(cp > 0) //Other conditionals unnecessary
			{

				hold1 = *(name+i);			//Sorts names
				*(name+i) = *(name+i+1);
				*(name+i+1) = hold1;

				*hold2 = *(acn+i);			//Sorts account numbers
				*(acn+i) = *(acn+i+1);
				*(acn+i+1) = *hold2;

				*hold3 = *(amt+i);			//Sorts money amounts
				*(amt+i) = *(amt+i+1);
				*(amt+i+1) = *hold3;	
			}
		}
	}	
	free(hold1);
	free(hold2);
	free(hold3);
}

