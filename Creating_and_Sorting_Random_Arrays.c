/*Aaron M. Smith
  Description: This lab involves using functions and the creation of two arrays with random numbers, 
  counting the repetition of a number, and counting common numbers. At the end it also involves sorting the arrays.
  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*********************************************FUNCTION PROTOTYPES********************************/

int check_error(int);
void initialize_array(int[],int);
void print_array(const int[],int);
float average(int[],int);
int count_numbers(int[],int,int);
int common_numbers(int[],int[],int);
void sort(int[],int); //For bonus

/***********************************************BEGIN MAIN****************************************/
int main(void)
{
srand(time(NULL));

int size,b;
int array1[100],array2[100];
printf("Enter the size of the array: "); //The user will input the size of the array
scanf("%d",&size);

b = check_error(size);

while (b != 1) //The while loop will make sure the input is valid
{
	printf("Invalid input, please enter the size of the array again: ");
	scanf("%d",&size);
	b = check_error(size);
}



//****************************************GIVING THE ARRAY VALUES AND AVERAGING****************************/
//Initializing and finding average with the first array:
initialize_array(array1,size);
printf("\nThe first input array\n");
print_array(array1,size);
printf("\n");

float average1;
average1 = average(array1,size); //finds average of values in array1

//Initializing and finding the average with the second array
initialize_array(array2,size);
printf("\nThe second input array\n");
print_array(array2,size);
printf("\n");

float average2;
average2 = average(array2,size); //finds average of values in array2

//Information Relay of the Averages
printf("\nAverage of numbers in the first array is %0.3f\n",average1);

printf("\nAverage of the numbers in the second array is %0.3f\n",average2);


//*************************************NUMBER COUNTING***********************************************/
//The following block of code will get a count for a number in each array
int numbercount,totalcount1,totalcount2;
printf("\nEnter a number: "); //The user wants to count how many times a number can be found in the array
scanf("%d",&numbercount);

totalcount1 = count_numbers(array1,size,numbercount); //count for array 1
totalcount2 = count_numbers(array2,size,numbercount); //count for array 2

printf("\nThe count of number %d in the first array is %d\n",numbercount,totalcount1);
printf("\nThe count of number %d in the second array is %d\n",numbercount,totalcount2);


//************************************COMMON COUNTING***********************************************/
//The following block of code will get a count for the number of values the arrays have in common

int common;

common = common_numbers(array1,array2,size);

printf("\nThe number of common numbers in the two arrays is %d\n",common);


//***********************************BONUS PART**************************************************/
//Sorting the arrays

printf("\n\nBonus part!\n\n");
printf("Array before sorting\n");
print_array(array1,size);
printf("\n");
print_array(array2,size);

sort(array1,size); //sends array1 to be sorted
sort(array2,size); //sends array2 to be sorted

printf("\nArray after sorting\n"); //Prints sorted arrays.
print_array(array1,size);
printf("\n");
print_array(array2,size);

printf("\n");

	return 0;
}
/**********FUNCTIONS**********/

int check_error(int x) //Function used to make sure integer number is between 0 and 100
{
	int result;
	if(x <= 0 || x > 100) //x needs to be between 0-100
		result = 0;
	else
		result = 1;

	return result; //Returns function result
}

void initialize_array(int a[],int b ) //Assigns values to the array
{
	int i;
	for (i=0; i < b; ++i)
	{
		a[i] = rand() % 10;
	}
}

void print_array (const int a[],int b) //Prints the values of the array
{
	int i;
	for (i=0; i<b; ++i)
	{
		printf("%2d",a[i]);
	}
}

float average(int a[],int b) //This function finds an average of the total of the values in an array
{
	int i;
	int total = 0;
	float average;
	for (i=0; i<b; i++)
	{
		total += a[i];
	}

	average = (float)total/b;

	return average;
}

int count_numbers(int a[],int b,int number) //This function counts the amount of time a number can be found in an array
{
	int i;
	int counter = 0;

	for(i = 0; i < b; i++)
	{
		if ( a[i] == number )
			++counter;
	}

	return counter;
}

int common_numbers(int c[], int d[],int b) //This function takes in two arrays and counts how many numbers are in common at the same index
{
	int i=0; //counter for array1
	int j=0; //counter for array2
	int counter=0;

	for(i = 0; i < b; i++)
	{
		if(c[i] == d[j++])
			++counter;
	}
	return counter;
}

void sort(int a[],int b) //sorts an array in ascending order.
{
	int pass;
	int i;
	int holdvalue;
	
	for(pass = 1; pass < b; pass++)
	{
		for(i = 0; i< b-1 ; i++)
		{	
			if (a[i] > a[i+1])
			{
				holdvalue = a[i]; //These lines allow the a[i] and a[i+1] to switch values
				a[i] = a[i+1];
				a[i+1] = holdvalue;
			}
		}
	}
}
			
			



