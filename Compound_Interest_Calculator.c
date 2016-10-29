/*Aaron M. Smith
  This program will calculate the Compound Interest earned on an income based on one of three different bank account types.*/

#include <stdio.h>
#include <math.h> //Includes the math library.

int main(void)
{

/*The first block of code gets an  account type from the person using the program. There are only three types of accounts,
  so if the user chooses a number that doesn't designate an account type, the program will ask for another one.*/
	int type;
	while( type < 1 || type > 3)
	{
		printf("\nBank Account Type\n\n");
		printf("(1) Checking\n");
		printf("(2) Saving\n");
		printf("(3) Fixed Deposit\n");
		printf("Please make a selection: ");
		scanf("%d",&type);
	
			if( type < 1 || type > 3)
			printf("Invalid choice, please make a choice again\n");
	}

/*The second block of code gets a year value  from the person using the program. It needs to be between 1 and 10 for the 
  program to function properly. If the person enters a number outside of the range, the program will ask for a new one.*/
	
	int year;
	while( year < 1 || year > 10)
	{
		printf("\nEnter a year: ");
		scanf("%d",&year);

		if( year < 1 || year > 10 )
			printf("Incorrect value, year should be 1-10\n");
	}
/*The next block of code asks the user for an amount of money in his or her account.*/

	float money = 0;
	
	printf("\nEnter the amount: ");
	while( money <= 0)
	{ 
		scanf("%f",&money);
		
		if(money <= 0)
			printf("Incorrect value, enter the amount again: ");
	}

/*The next block of code decides which interest rate should be used, depending on the account type selected. The interest rates
  for checking, savings, and fixed deposit are 1%, 3% and 7% respectively.*/
	
	int rate;

	switch(type)
	{
		case 1:
			rate = 1;
			break;

		case 2:
			rate = 3;
			break;

		case 3:
			rate = 7;
			break;
	}

/*At this point, the program should have all the variables it needs to use the interest equations. The first finds the new
  amount with interest:

  	AmountCI = Amount*(1+rate/100)^year*/

	float AmountCI, a, b;

	a = 1+(float)rate/100;

	b = pow(a,year);

	AmountCI = money*b;

/*The second equation finds the interest earned by subtracting the new amount from the old one*/

	float InterestEarned;

	InterestEarned = AmountCI - money;

/*The user must be told how their account has changed*/

	printf("\nThe amount after %d years is %0.2f",year,AmountCI);

	printf("\nThe interest earned on the amount %0.2f is %0.2f",money,InterestEarned);


	float x;
	float y;
	int n;
	int counter;
	float z;
	
	printf("\n\nExtra\n");
	printf("\nEnter a number: ");
	scanf("%f",&x);

	printf("\nEnter an exponent: " );
	scanf("%d",&n);

/*If n = 0, the value will be one. (It's a math law X^0 = 1) */

	if(n == 0)
	{
		printf("pow(%0.2f, %d) = 1\n",x,n);
	}
	
/*If n >= 1, it should multiply x*x, n times. A for loop is useful: */
	y = x;
	if(n >= 1)
	{
		for( counter = 1 ; counter < n ; ++counter)
		{
		   y = y*x;
		}
		 printf("pow(%0.2f,%d) = %0.2f\n",x,n,y);
	}

/*If n < 0, it should divide x/x, accordingly.*/
	y = x;
	if (n < 0)
	{
		for(counter = -1 ; counter >= n; --counter)
		{
			y = y*x;
		}

		/*Reversed*/

		z = x/y;
		printf("pow(%0.2f,%d) = %f\n",x,n,z);
	}
	return 0;
}
