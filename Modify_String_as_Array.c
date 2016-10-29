/*Aaron M. Smith
  This program uses array notation to find the length and modify a string.
*/

#include <stdio.h>

/********************FUNCTION PROTOTYPES********************/

int length(char s[]);
int replace(char s[],int i);
void copy(char s[], char s2[]);
void merge(char s[], char s1[], char s2[]);
void sort_string(char s2[]);

/********************MAIN********************/
int main(void)
{
	int i; //Counter

	//**********the first part of this program asks the user to input a string. The program informs the user how long the string is.*****
	char s[20]; //initializes a character array. Given size 20.

	printf("\nEnter a string : ");  //Asks user to input string
	scanf("%19s",s); 				//Reads whatever the user inputs

	printf("\nFirst string is ");
	for(i = 0; s[i] != '\0' ;i++)
		printf("%c",s[i]);

	int stringsize; 		//Initializes an integer for the size of the string
	stringsize = length(s); //Sends string to a function to be read
	printf("\nLength of the string is %d ",stringsize); //Prints length

	//**********the second part of this program copies the first array and places it in a new one.*****
	
	char anotherone[20]; //Makes a new array to store the copy
	
	copy(s,anotherone);  //Sends the array to be copied

	printf("\nCopy of the first string is "); //the next lines print the copy.
	for(i = 0; anotherone[i] != '\0'; i++)
	{
		printf("%c",anotherone[i]);
	}

	//**********the third part of this program asks the user to change a position to '#'. It reads a position and changes the string.*****

	printf("\n"); //Separation
	int replacement;
	printf("\nEnter a position for the  replacement operation: ");
   	scanf("%d",&replacement); //Figures out what character the user wants to replace

	int check;
	check = replace(s,replacement-1); //-1 because array index begins at 0, while the user thinks a word begins at 1

	switch(check) //Makes sure the user chose a valid position and prints accordingly
	{
		case 0:
		printf("Invalid position");
		break;

		case 1:
		printf("String after replacement option is ");
		for(i = 0; s[i] != '\0' ; i++)
		{
			printf("%c",s[i]);
		}
		break;
	}

	//**********the fourth part of this program merges the first array with a new one chosen by the user*****

	printf("\n");
	
	char s2[20]; 	  //Creates new array that the user inputs.
	printf("\nEnter second string : "); //the question
	scanf("%19s",s2); //the delivery

	printf("\nSecond string is "); //Prints second string.
	for(i = 0; s2[i] != '\0'; i++)
	{
		printf("%c",s2[i]);
	}

	char m[40]; //creates an array that will become the merged form of the first and second array

	merge(s,s2,m);
	
	printf("\nMerged string is "); //Information is printed
	for(i = 0; m[i] != '\0'; i++)
	{
		printf("%c",m[i]);
	}
	printf("\n");

	//**********this part of this program sorts the merged array*****
	printf("\nSorting!\n");
	printf("\nString before sorting\n");
	for(i = 0; m[i] != '\0'; i++)
	{
		printf("%c",m[i]);
	}
	printf("\n");

	sort_string(m); //this function sorts and prints the array

	return 0;
}

/********************FUNCTIONS********************/

int length(char s[]) //Finds the length of the string array
{
	int i;
	int size = 0;
	for(i = 0; s[i] != '\0' ; i++)
	{
		size++;
	}

	return size;
}

int replace(char s[],int i) //Replaces a character with #
{
	int result;
	int x;
	x = length(s);

	if (i > 0 && i < x)
	{
		s[i] = '#';
		result = 1;
	}
	else
		result = 0;

	return result;
}

void copy(char s[], char anotherone[]) //Copies an array into a new one
{
	int i;
	int size;

	size = length(s);

	for(i = 0; i < size ; i++)
	{
		anotherone[i] = s[i];
	}
	
	anotherone[size+1] = '\0';
}

void merge(char s[],char s2[],char m[])
{
	int i; //The all powerful counter
	int j; //Another counter for good measure

	int size1 = length(s); //Finds the length of the first array for use in the merge
	int size2 = length(s2); //Finds the length of the second array.
	
	for(i = 0; i < size1 ; i++) //copies array 1 into the merger
	{
		m[i] = s[i];
	}

	for(j = size1; j < size1+size2; j++) //copies array 2 into the merger
	{
		m[j] = s2[j-size1];
	}

	m[size1+size2] = '\0';
}

void sort_string(char m[]) //this function sorts the character array
{
	int pass;
	char hold;
	int size;
	int i;

	size = length(m);

	for(pass = 1; pass < size ; pass++) //The following lines will sort the array so that the "small to big/alphabetical" order
	{
		for(i = 0; i < size-1 ; i++)
		{
			if(m[i] > m[i+1])
			{
				hold = m[i];
				m[i] = m[i+1];
				m[i+1] = hold;
			}
		}
	}

	m[size] = '\0';

	printf("\nString after sorting\n"); //sorted array is printed
	for(i = 0; m[i] != '\0' ; i++)
	{
		printf("%c",m[i]);
	}

	printf("\n"); //separation
}
			

