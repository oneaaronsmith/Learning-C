/*Aaron M. Smith
  This program reads 2 integers from the user and performs several operations
  with them. It also calculates the total distance travelled
  by a vehicle given an initial speed and acceleration.*/

#include <stdio.h>

int main (void)
{
	/*These first lines introduce integers for us in this program.
	   a and b are chosen by the user.*/

	int a,b,sum,product,quotient1,remainder1,quotient2,remainder2;

	printf("Enter the first number:");
	scanf("%d",&a);
	printf("\n");

	printf("Enter the second number:");
	scanf("%d",&b);
	printf("\n");

	/*These next lines perform arithmetic operations with the numbers
	  chosen by the user*/

		sum			 = a+b;
		product		 = a*b;
		quotient1	 = a/b;
		remainder1	 = a%b;
		quotient2	 = b/a;
		remainder2	 = b%a;

	/*The following lines report the program's findings*/

	printf("The sum of %d and %d is %d\n",a,b,sum);
	printf("The product of %d and %d is %d\n",a,b,product);
	printf("For %d divided by %d quotient is %d and remainder is %d\n",a,b,
			quotient1,remainder1);
	printf("For %d divided by %d quotient is %d and remainder is %d\n",b,a,
			quotient2,remainder2);
	
	/*To find which number is bigger, I used two separate if statemtents"*/

	if (a > b)
	{
		printf("%d is the bigger number\n",a);
	}
	if (b > a)
	{
		printf("%d is the bigger number\n",b);
	}

	/*I also used if statements to check whether the numbers were even
	  or odd*/

	if (a % 2  == 0)
		printf("%d is an even number\n",a);
	else
		printf("%d is an odd number\n",a);

	if (b % 2 == 0)
		printf("%d is an even number\n",b);
	else
		printf("%d is an odd number\n",b);
	
	
	/*These first lines read in data from the user for velocity, 
	  acceleration, and time*/
	int  u,acc,t;
	
	printf("Enter the initial velocity: "); /*miles/hour*/
	scanf("%d",&u);
	printf("Enter the acceleration: "); /*miles/hour^2*/
	scanf("%d",&acc);
	printf("Enter the time: "); /*seconds*/
	scanf("%d",&t);

	/*For a precise answer, the distance is calculated as a float
	  variable*/

	float d, m, time;

	time = (float)t/3600;

	d = ((float)u*(float)time) + ((float)acc*((float)time*(float)time))/2;

	m = d * 1600 ; /*converts miles to meters*/

	/*The result is given to the user*/

	printf("Total distance travelled by the vehicle in %d seconds is %f miles or %f meters",t,d,m);

	return 0;
}
