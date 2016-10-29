/*Aaron M. Smith
  Purpose: Parsing a file */

/*****LIBRARIES*****/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

/*****PROTOTYPES*****/
int isPhoneNumber(char* token);
int isDate(char* token);
int isEmail(char* token);
/*****MAIN*****/
int main(int argc, char *argv[]) 
{
	//Ensure valid input.
	if(argc != 2)
	{
		printf("Insufficient arguments at command line.\n <./a.out> <input.txt>\n");
		return 0;
	}
	
	//Open file and figure out how long it is.
	FILE* fp = fopen(argv[1],"r");
	char c;
	int length = 0;
	while(!feof(fp))
	{
		fscanf(fp,"%c",&c);
		length++;
	}
	fclose(fp); //close the file
	
	//Reopen the file, and scan it into an string.
	FILE* file = fopen(argv[1],"r");
	int i = 0;
	char* p;
	p = malloc(sizeof(char)*length); //malloc space from length we found.
	for(i = 0 ; i < length; i++)
	{
		fscanf(file,"%c",&p[i]);
	}
	
	fclose(file); //close the file.
	
	//Tokenize the string
	char* stringtokens;
	stringtokens = strtok(p," !,?");
	
	while(stringtokens != NULL)
	{		
		if(isEmail(stringtokens) == 1)
			printf("\nEmail: %s",stringtokens);
		if(isPhoneNumber(stringtokens) == 1)
			printf("\nPhone Number: %s",stringtokens);
		if(isDate(stringtokens) == 1)
			printf("\nDate: %s",stringtokens);
		
		stringtokens = strtok(NULL," !,?");
	}
	
	//Free all malloced space and separate line.
	printf("\n");
	free(p);
	return 0;
}

/*****FUNCTIONS*****/
int isDate(char* token)
{
	/*This function will read in a string and determine if it is a valid date. It must have the structure
	  XX/XX/XXXX. (MM/DD/YYYY) Months must be between 1-12 and the year must be after 2000. Days must
	  fit within the parameters of the given month. Year must be after 2000. 
	  If it is a valid date, function returns 1, otherwise 0.*/
	  
	  int i; //counter for loops
	  char* month = malloc(sizeof(char)*2); //this will keep track of the month
	  char* day = malloc(sizeof(char)*2);  //this will keep track of the day.
	  char* startmonth = month; //this will keep track of the beginning of month
	  char* startday = day;		//this will keep track of the beginning of day.
	  char* start = token; //Keep track of the beginning.
	  int monthvalue;
	  int dayvalue;
	  
	//This checks to make sure the first two numbers are correct. Proceeds if it is.
	if(*token == '0' || *token == '1')
	{
		*month = *token;
		token++;
	}
	else
	{
		free(month);
		free(day);
		return 0;
	}
	
	if(*month == '0') //If the first integer is 0, the next must be between 1-9
	{
		if(isdigit(*token) != 0 && *token != '0')
		{
			*month = *token;
			++token;
		}
		else
		{
			free(month);
	        free(day);
			return 0;
		}
	}
	
	if(*month == '1') //If the first integer is 1, the next must be between 0-2
	{
		if(*token == '0' || *token == '1' || *token == '2')
		{
			++month;
			*month = *token;
			month = startmonth;
			++token;
		}
		else
		{
			free(month);
	        free(day);
			return 0;
		}
	}
	
	//***CHECK FOR '/'
	
	if(*token == '/') //Begin by making sure the first character is an slash.
	{
		++token; //If it is a slash, continue parsing
	}
	else
	{
		free(month);
	    free(day);
		return 0; //If it is not a slash, the token is invalid.
	}
	
	//****CHECK THE DATE****
	
	  if(*token == '0') //if date starts with 0, the next must be 1-9
	  {
		  ++token;
		  if(isdigit(*token) == 0 || *token == '0')
		  {
			  free(month);
			  free(day);
			  return 0;
		  }
		  else
		  {
			  *day = *token;
			  token++;
		  }
	  }
	  else if(*token == '1' || *token == '2' || *token == '3') //if the date starts is 1-3, the next must be 0-9
	  {
		  *day = *token;
		  ++token;
		  ++day;
		  if(isdigit(*token) == 0)
		  {
			  free(month);
			  free(day);
			  return 0;
		  }
		  else
		  {
			  *day = *token;
			  day = startday;
		  }
	  }
	  
	  
	 //Convert months and dates to integers for comparison. Only let valid dates for valid months pass by.
	  monthvalue = atoi(month);
	  dayvalue = atoi(day);
	  
	  if(monthvalue == 1 || monthvalue == 3 || monthvalue == 5 || monthvalue == 7 || monthvalue == 8 || monthvalue == 10 || monthvalue == 12)
	  {
		  if(dayvalue > 31 || dayvalue <= 0)
		  {
			  free(month);
			  free(day);
			  return 0;
		  }
	  }  
	  
	  if(monthvalue == 2)
	  {
		  if(dayvalue > 28 || dayvalue <= 0)
		  {
			  free(month);
			  free(day);
			  return 0;
		  }
	  }
	  
	  if(monthvalue == 4 || monthvalue == 6 || monthvalue == 9 || monthvalue == 11)
	  {
		  if(dayvalue > 30 || dayvalue <= 0)
		  {
			  free(month);
			  free(day);
			  return 0;
		  }
	  }
	  
	  token++;
	//****CHECK FOR SLASH AGAIN
	if(*token == '/') //Begin by making sure the first character is an slash.
	{
		++token; //If it is a slash, continue parsing
	}
	else
	{
		free(month);
	    free(day);
		return 0; //If it is not a slash, the token is invalid.
	}
	
	//CHECK FOR YEAR
	if(*token == '2')
	{
		++token;
	}
	else
	{
		free(month);
		free(day);
		return 0;
	}
	
	for(i = 0; i < 3; i++)
	{
		if(isdigit(*token) == 0)
		{
			free(month);
			free(day);
			return 0;
		}
		++token;
	}
	
	//IF THE DATE HAS BRAVED THE STORM FREE MALLOC SPACE AND RETURN 1-12
	token = start;
	free(month);
	free(day);
	return 1;
		
}
int isPhoneNumber(char* token) 
{
 /*This function will read in a string and determine if it is a valid phone number. This number
   must have the structure of (XXX)XXX-XXXX or it will be considered invalid. Function will return 1
   if it is valid and zero if it is invalid.*/
	  
	int i; 				 //a counter to be used in "for" loops
	char* start = token; //Remember where the beginning was by saving the address of the character
	
	if(*token == '(') //Begin by making sure the first character is an open parenthesis.
	{
		++token; //If it is an open parenthesis, continue parsing
	}
	else
	{
		return 0; //If it is not an open parenthesis, the number is invalid.
	}
	
	//Next, the function checks to see if the next three characters are numbers. If not, it will return 0.
	for(i=0; i < 3 ; i++)
	{
		if(isdigit(*token) == 0)
		{
			return 0;
		}
		++token;
	}
	
	//The function will determine if the area code is followed by a closed parenthesis.
	if(*token == ')')
	{
		++token; //If it is a closed parenthesis, continue parsing
	}
	else
	{
		return 0; //If it is not a closed parenthesis, the number is invalid.
	}
	
	//Next, the function checks to see if the next three characters are numbers. If not, it will return 0.
	for(i=0; i < 3 ; i++)
	{
		if(isdigit(*token) == 0)
		{
			return 0;
		}
		++token;
	}
	
	//Next, the function determines if there is a dash XXX-XXXX
	if(*token == '-')
	{
		++token; //If it is a dash, continue parsing
	}
	else
	{
		return 0; //If it is not a dash, continue parsing.
	}
	
	//The function finishes parsing if the next four characters are numbers.
	for(i=0; i < 4 ; i++)
	{
		if(isdigit(*token) == 0)
		{
			return 0;
		}
		++token;
	}
	
	token = start; //reset the pointer at the beginning of the string.
	return 1;
		
}

int isEmail(char* token)
{
	if(isalnum(*token) == 0)
		return 0;
	else
	{
		while(isalnum(*token) != 0)
		{
			token++;
		}
	}
	
	if(*token == '@')
		++token;
	else
	{
		return 0;
	}
	
	if(isalnum(*token) == 0)
		return 0;
	else
	{
		while(isalnum(*token) != 0)
		{
			token++;
		}
	}
	
	if(*token == '.')
		++token;
	else
		return 0;
	
	if(*token == 'c')
		++token;
	else
		return 0;
	
	if(*token == 'o')
		++token;
	else
		return 0;
	
	if(*token == 'm')
		++token;
	else
		return 0;
	
	return 1;
}

