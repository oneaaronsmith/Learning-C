/*Aaron M Smith
  This program uses pointer notation to modify strings
*/
#include <stdio.h>
#include <stdlib.h>

/********************FUNCTION PROTOTYPES********************/

void printpoint(char *s); 			//Prints a string based on pointer arithmetic
int length(char *s); 	  			//Takes a pointer (holds address) and returns length of the string
char* copy(char *s); 	  			//Copies content of one string into another.
char* reverse(char *s);   			//Takes a string, returns pointer for reversed string
void clear(char *s); 	  			//Takes a pointer and free use the memory
int search(char *s,char c); 		//Searches pointer for a character
int prefix(char *s1,char *s2); 		//Checks to see if a string is a prefix to another string
void new_merge(char *s1,char *s2);

/********************MAIN BEGINS HERE**********************/
int main(void)
{
	/**********The first section of this code has the user input a string and prints it**********/

	char *str1; 	 						//Initializes a string pointer
	str1 = (char *)malloc(sizeof(char)*10); //Allocates space to the pointer

	if(str1 == NULL) 						//This if statement makes sure the pointer has valid address
	{
		printf("\nERROR: Out of memory\n"); //A valid address will not be given if there is no memory left
		return 1; 							//Ends program if NULL
	}

	printf("\nEnter a string: "); //Asks user to input a string
	scanf("%s",str1);
	printf("\nThe first string is "); 
	printpoint(str1); 			  //Calls a function to prints the string that the user inputs

	/**********The second part of this code determines the string length and copies it**********/

	int size; 			 //Initializes an integer to hold the length of the string
	size = length(str1); //Calls function to determine length
	printf("\nLength of the string is %d",size);

	char *copyofstring;  //Initializes a pointer to become the new copy

	copyofstring = copy(str1); //Call a copy function to copy the string.

	printf("\nCopy of first string is ");
	printpoint(copyofstring);  //Prints it

	/*********The third part of this code creates and prints a reverse of the string**********/

	char *reverseflash; //Initializes a pointer

	reverseflash = reverse(str1);

	printf("\nReverse of the string %s is ",str1);
	printpoint(reverseflash);

	printf("\n"); //A separation for good measure

	/********The fourth part of this code asks user to search for a letter/number in their string and it prints the index location.*****/
	int index = -1;	
	char searchchoice; 

	while(index == -1)
	{
		printf("\nEnter a character for the search operation: ");
		scanf("%c",&searchchoice); //For whatever reason, it seems as if the program skips this the first time
		index = search(str1,searchchoice);
	}
	

	printf("Character %c is present at the index %d in the string %s",searchchoice,index,str1);

	/**********The fifth part of this code asks the user to check for a prefix.**********/
	
	char *stra; //Initializes stra
		stra = (char *)malloc(sizeof(char)*10);
	char *strb; //Initialize strb
		strb = (char *)malloc(sizeof(char)*10);

	int prefixcheck;

	printf("\n\nEnter a string for the prefix operation: ");
		scanf("%s",stra);

	printf("\nEnter a string to check for prefix: ");
		scanf("%s",strb);

	prefixcheck = prefix(stra,strb); //Sneds informatin to function

	if(prefixcheck == 1)
		printf("\n%s is a prefix of the string %s",strb,stra);
	else
		printf("\n%s is not a prefix of the string %s",strb,stra);

	printf("\n");

	
	/********CLEARS DATA**********/
	clear(str1);
	clear(copyofstring);
	clear(reverseflash);
	clear(stra);
	clear(strb);

	return 0;
}

/********************FUNCTIONS (ALSO, MAIN HAS ENDED)****************************/

void printpoint(char *str) //Prints strings given pointer
{
	char *hold; //Saves the address of the pointer
	hold = str;

	while(*str != '\0')
	{
		printf("%c",*str); //Prints the individual parts of the string
		str++;
	}

	str = hold; //Returns pointer to the original address
}

int length(char *str1)
{
	char *hold;
	hold = str1;
	int size=0; //Initialized to 1 to account for index 0

	while(*str1 != '\0')
	{
		size++;
		str1++;
	}

	str1 = hold;
	return size;
}

char* copy(char *str1) //This function creates a copy of the original string
{
	char *str2; //Terms are initialized. The holds are meant to keep track of the original address.
	char *hold;
	char *hold2;

	hold = str1;
	int size2 = length(str1)+1; //Determines need for malloc

	str2 = (char *)malloc(sizeof(char)*size2);
	hold2 = str2;

	while(*str1 != '\0') //Gives the new string characters as a copy of the original
	{
		*str2 = *str1;
		str1++;
		str2++;
	}

	str1 = hold; //Address is reset to its original place

	str2++; //The copy recieves a NULL terminating factor
	*str2 = '\0';

	str2 = hold2; //Address is reset

	return str2;
}

char* reverse(char *str1) //This function creates a reverse of the original string
{
	char *hold; //Holds are created to store the original address. String three is initialized, 
	char *hold2;
	char *str3;
	int lengthofstr = length(str1)+1; //Finds how much pace we want to malloc

	str3 = (char *)malloc(sizeof(char)*lengthofstr);
	
	hold = str1; 		 //Holds are set
	hold2 = str3;

	int size = 0; 		 //These integeres are made to facilitate the following conditional statements
	int reversecounter;

	while(*str1 != '\0') //This gets string 1 to the final address in its array and keeps track of how long it is.
	{
		str1++;
		size++;
	}

	str1--; //String 1 is currently on a terminating factor, which would be troublesome for the new string. Thus, it is decreased by 1 address

	for(reversecounter = size; reversecounter != 0; reversecounter--) //String 1 is being reset while string 3 is being put together
	{
		*str3 = *str1;
		str1--;
		str3++;
	}
	
	str3++; 	  //These lines add the terminating factor to the reverse string
	*str3 = '\0';

	str3 = hold2; //String 3 is given its original address (uneccessary for string 1 since it is reset in the for loop)
	return str3;
}

void clear(char *str) //This function clears the string to return data
{
	free(str);
}

int search(char *str1,char c) //This function searches for a character in the string
{
	int i=0; //counter, begins at index 0
	int result;
	char *hold;

	hold = str1;

	while(*str1 != '\0')
	{
		if(*str1 == c)
		{
			result = i;
			break;
		}
		else 
			result = -1;
		
		str1++;
		i++;
	}

	str1 = hold;
	return result;
}


int prefix(char *stra, char *strb) //Checks to see if strb is a prefix of stra
{
	int result; //Initiliaze necessary variables and holds:
	char *hold1;
	char *hold2;
	hold1 = stra;
	hold2 = strb;

	while(*strb != '\0' && *stra != '\0') 
	{
		if(*strb != *stra) //If they are not equal, then it is NOT a prefix
			result = 0;
		else
			result = 1;

		strb++;
		stra++;
	}

	stra = hold1; //Reset address
	strb = hold2;

	return result; //Return result
}

/*void merge(char *str01, char *str02) BONUS PART (Comment out)
{
	char *hold1;
	char *hold2;
	char *hold3;

	hold1 = str01;
	hold2 = str02;

	int size1 = length(str01)+1;
	int size2 = length(str02);
	int size3 = size1 + size2;

	char *merged;
		merged = (char *)malloc(sizeof(char)*size3);

	hold3 = merged;

	int i;

	for(i = 0; i < size3 ; i++)
	{
		*merged = *str01;
		merged++;
		str01++;
		*merged = *str02;
		merged++;
		str02++;
	}

	merged++;
	*merged = '\0';

	merged = hold3;

	printf("\nNew merged string is %s",merged);
}*/

	


