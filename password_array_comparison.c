/*Aaron M Smith
  
  This program reads an account number and password from a file and stores them in two
  character arrays and displays the stored account number. If the account number is
  invalid, the user is prompted to change it. If the password is invalid, the user is
  prompted to change it.
  
*/

/***************LIBRARIES INCLUDED****************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/***************FUNCTION PROTOTYPES***************/

int load_data(char *filename, char *acn, char *pwd);
int checkAccountNumber(char *a, int n);
int checkUpperLetter(char *a);
int checkDigit(char *a);
int checkpwdLength(char *a, int n);
int checkSpecialchar(char *a);
int compare_strings(char *s1, char *s2);

/***************MAIN********************/

int main(int argc, char **argv) //input length of account # and password at command line
{
	/*
	  This program requires input from the command prompt. The input file name and the
	  length of account number and password will be provided as follows: 
	  argv[0] = ./a.out
	  argv[1] = input file name
	  argv[2] = integer length of account number and password
	*/

	if(argc != 3 )
	{
		printf("\nInsufficient arguments \n");
		printf("Please specify your file name and length of account number");
		return 0;
	}

	int s = atoi(*(argv+2));


	/**********The first section involves creation of account number and password pointers, and they receive information from a .txt file**********/

	char *acn; //Initializes a pointer to store the account number
	char *pwd; //Initializes a pointer to store the password

	acn = malloc(sizeof(char)*s); //Allocates space to the account number pointer
	pwd = malloc(sizeof(char)*s); //Allocates space to the password pointer

	int status = load_data(*(argv+1),acn,pwd); //loads data from txt file

	if(status == 0) //If opening unsuccessful, an error is displayed
	{
		printf("\nError: Unable to open input file \n"); //The user has been served
		return 0;
	}

	printf("\n\nAccount number is %s\n",acn); //Initial account number is printed
	printf("Password is %s\n",pwd);			  //Initial password is printed

	/**********The following section is incorporated to make sure the account number fits needed criteria**********/

	int accountcheck =  checkAccountNumber(acn,s); //calls check function and sends account pointer and size

	while(accountcheck != 1) //If account does not meet requirements, the user creates a new account number.
	{
		printf("Enter the account number again: ");
		scanf(" %s",acn);
		accountcheck = checkAccountNumber(acn,s);
	}

	printf("Your account number is %s\n",acn); //New number is printed

	/**********The following section is incorporated to make sure the password fits needed criteria****************/

	int digit, upper, lengthcheck, special, passcheck;

	upper = checkUpperLetter(pwd); 			//1 if there is an uppercase letter, 0 if otherwise.
	
	digit = checkDigit(pwd);	   			//1 if there is a number, 0 if otherwise.

	lengthcheck = checkpwdLength(pwd, s);	//1 if the length is proper, 0 if otherwise.

	special = checkSpecialchar(pwd);		//1 if there is a special character, 0 if otherwise.

	while(digit == 0 || upper == 0 || lengthcheck == 0 || special == 0 ) //until the password is good, the program will ask for a change
	{
		if(lengthcheck != 1) //if the password has an improper length, the user must change the password
		{
			printf("\nInvalid password. Password should be 6 characters long.\nEnter the Password again: ");
			scanf(" %s",pwd);
			digit = checkDigit(pwd);
			upper = checkUpperLetter(pwd);
			lengthcheck = checkpwdLength(pwd, s);
			special = checkSpecialchar(pwd);
			continue;		
		}

		if(upper != 1) //if there is no upper case letter, the user must change the password
		{
			printf("\nThere should be at least one upper case character in the password.\nEnter the password again: ");
			scanf(" %s",pwd);
			digit = checkDigit(pwd);
			upper = checkUpperLetter(pwd);
			lengthcheck = checkpwdLength(pwd, s);
			special = checkSpecialchar(pwd);
			continue;		
		}

		if(digit != 1) //if there is no number, the user must change the password
		{
			printf("\nThere should be at least one number in the password.\nEnter the password again: ");
			scanf(" %s",pwd);
			digit = checkDigit(pwd);
			upper = checkUpperLetter(pwd);
			lengthcheck = checkpwdLength(pwd, s);
			special = checkSpecialchar(pwd);
			continue;	
		}

		if(special != 1) //if there is no special character, the user is prompted to change the password
		{
			printf("\nThere should be at least one special character in the password.\nEnter the password again: ");
			scanf(" %s",pwd);
			digit = checkDigit(pwd);
			upper = checkUpperLetter(pwd);
			lengthcheck = checkpwdLength(pwd, s);
			special = checkSpecialchar(pwd);
			continue;

		}
	}

	printf("\nYour account is successfully created.\n\n");	//final information begins printing
	printf("Account number: %s\nPassword: %s\n",acn,pwd);

	/**********The malloc space is cleared and the program ends**********/
	free(acn);
	free(pwd);

	/**********BONUS**********/
	printf("\nBonus Part\n");
	
	char *str1,*str2; //initialize strings to compare

	str1 = malloc(sizeof(char)*30); //malloc space for string 1
	str2 = malloc(sizeof(char)*30); //malloc space for string 2

	printf("\nEnter the first string: ");
	scanf("%s",str1);

	printf("\nEnter the second string: ");
	scanf("%s",str2);

	int cp; //Used to carry the result

	cp = compare_strings(str1,str2); //Calls the function

	if(cp == 1)
		printf("\nstring1 is bigger than string 2\n");
	if(cp == -1)
		printf("\nstring1 is smaller than string 2\n");
	if(cp ==0)
		printf("\nThe two strings are equal\n");

	return 0;
}

/********************FUNCTIONS*************************/

int load_data(char *filename, char *acn, char *pwd)
{
	/*Load data takes the input file name and two character arrays. It opens the input
	  file and returns 0 if unsuccessful. Otherwise, load_data loads the account number
	  and password from the text file into the character arrays and returns 1. */
	int l = strlen(acn);

	FILE* file = fopen(filename, "r"); //opens the input .txt file for reading

	if(file == NULL)
	{
		return 0;
	}

	char *fileacn = malloc(sizeof(char)*l); //Creates pointer for input account
   	char *filepwd = malloc(sizeof(char)*l); //Creates pointer for input password

	fscanf(file,"%s %s",fileacn,filepwd);

	strcpy(acn,fileacn); //Stores input account info in a pointer
	strcpy(pwd,filepwd); //Stores input password info

	free(fileacn); //Their services are no longer required.
	free(filepwd);
	
	fclose(file);
	return 1;
}

int checkAccountNumber(char *acn, int n)
{
	int i; 					  //i will act as a counter for the pointer arithmetic
	int length = strlen(acn); //the length of the string
	int a; 					  //a will act as an integer holder for the isdigit values.
	int errorcount = 0;
	
	if(length != n) 		  //Account length must meet requirement.
	{
		printf("\nInvalid account number. Account should be a 6 digit number\n");
		return 0;
	}

	for(i = 0; i < n; i++) //This for loop checks to see if the account is entirely made up of digits
	{
		a = isdigit(*(acn+i));
		if(a == 0)
		{
			errorcount++;  //If any character is not a digit, the error count is bumped so the function  will return a 0
		}
	}

	if(errorcount != 0)    //If there were any non-digit characters, the program returns an error message and 0
	{
		printf("\nInvalid account number. Account should be a 6 digit number\n");
		return 0;
	}

	return 1; 			   //If account number is valid, function returns 1
}

int checkUpperLetter(char *a) //checks for uppercase letters in a string
{
	int length = strlen(a);
	int i;
	int b; //will act as an integer holder for the ctype isupper function values
    int upper = 0; //will act as a counter for uppercase letters

	for(i = 0; i < length; i++)
	{
	    b = isupper(*(a+i)); //if character is an uppercase letter, the upper counter is bumped
		if(b != 0)
		{
			upper++;
		}
	}
	
	if(upper > 0) //If there was an uppercase letter, the function returns 1
	{
		return 1;
	}

	return 0;
}

int checkDigit(char *a) //checks for a digit in a string
{
	int length = strlen(a);
	int i;
	int c; //will act as an integer holder for the ctype isdigit function values
	int digit = 0; //will act as a counter for digits

	for(i = 0; i <= length; i++)
	{
		c = isdigit(*(a+i)); //for all characters in the password, if it is a digit, the digit counter is bumped
		if(c != 0)
		{
			digit++;
		}
	}

	if(digit > 0) //if there is a digit in the string, the function returns 1
	{
		return 1;
	}

	return 0;
}

int checkpwdLength(char *a, int n) //checks to see if the length of the string is the same as the command prompt.
{
	int length = strlen(a);

	if(length != n) //if length is improper, returns 0
		return 0;

	return 1;
}

int checkSpecialchar(char *a) //checks for special characters
{
	int length = strlen(a);
	int i;  //a counter
	char d; //will act as a character holder for the special finder.
	int special = 0; //will act as a counter for special characters

	for(i = 0; i <= length; i++)
	{
		d = *(a+i);
		if(d == '$' || d == '#' || d == '(' || d == ')' || d == ';' || d == ':' || d == '%' || d == '{' || d == '}' || d == '?') 
		{
			special++;
		}
	}

	if(special > 0) //if there is at least one special character, the functino returns 1.
	{
		return 1;
	}

	return 0;
}

int compare_strings(char *str1, char *str2) //compares size of strings (bonus)
{
	int i; // a counter
	int length1 = strlen(str1); //length of string 1
	int length2 = strlen(str2); //length of string 2
	int strength1 = 0;			//
	int strength2 = 0;
	int lengthchoice;

	if(length1 > length2) //Makes sure the right length is used
		lengthchoice = length1;
	else
		lengthchoice = length2;

	for(i = 0; i < lengthchoice ; i++) //Adds up the values of the characters of each string to determine which is bigger
	{
			strength1+= (int)*(str1+i);
			strength2+= (int)*(str2+i);
	}

	if(strength1 > strength2) //If string1 is bigger, returns 1
		return 1;
	
	if(strength1 < strength2) //If string1 is smaller, returns -1
		return -1;

	if(strength1 == strength2) //If the strings are equal, returns 0
		return 0;
}

//FIN
