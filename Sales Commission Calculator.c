/*Aaron M. Smith
  This program involves the creation of a Sales Commission Calculator through the use of a while loop and conditional statements.*/

#include <stdio.h>

int main (void)
{
	int quit;
	while (quit != -1)
	{
	/*The first part of this program will ask the user to input the employee type. The options are 1 and 2 for part time and full time employees respectively.*/
	int employee; /* This will be dependent on the selection, and will designate employee type.*/
	int selection; /*Employee type read by user*/
	
	printf("\nEmployee type\n (1) Part time\n (2) Full time\n");
	printf("Please make a selection: ");
	scanf("%d",&selection);

	if (selection <= 0)
	{
		printf("Invalid choice, make a selection again: ");
		scanf("%d",&selection);
	}
	if (selection > 2)
	{
		printf("Invalid choice, make a selection again: ");
		scanf("%d",&selection);
	}
	if (selection == 1)
	{
		selection = 1;
		printf("You have selected %d (Part Time) \n \n",selection);
	}

	if (selection == 2)
	{
		selection = 2;
		printf("You have selected %d (Full Time) \n \n",selection);
	}

	employee = selection;

	/*The second part of the program calculates the commission and net income a  worker may receive. It is dependent upon employee type and weekly sales.*/

	int sales; /*Sales value made by employee in a week*/
	float total; /*Commission made by employee in a week.*/
	int  rate; /*Commission rate for employee.*/

		printf("Enter the weekly sales: ");
		scanf("%d",&sales);
		if (sales < 0)
		{
			printf("Error: Cannot have negative sales.\nEnter the weekly sales: ");
			scanf("%d",&sales);
		}

	/*The commission rates are different for part time and full time employees. The following lines will provide the commision rate.*/

		if (employee == 1)
		{
			if (sales >= 0)
				rate = 7;
			if (sales >  10000)
				rate = 10;
			if (sales > 20000)
				rate = 15;
			if (sales > 30000)
				rate = 17;
			if (sales > 50000)
				rate = 20;
		}
		if (employee == 2)
		{
			if (sales >= 0)
				rate = 5;
			if (sales > 10000)
				rate = 9;
			if (sales > 20000)
				rate = 12;
			if (sales > 30000)
				rate = 15;
			if (sales > 50000)
				rate = 20;
		}

		printf("Commission rate is %d%% \n",rate);

	/*The total commissions received can be calculated by the following: */

		total = ((float)sales *(float)rate)/100;

		printf("Total commission on sales is $%.2f \n",total);

	/*Net income is based on the commission and employee wage. It is different depending on employee type.*/

		int wage;

		if (employee == 1)
			wage = 200;
		if (employee == 2)
			wage = 300;

		float income;

		income = (float)wage + total;

		printf("Net income is $%.2f \n \n",income);

	/*The program may end if the user wishes it*/

		printf("Do you want to continue? type -1 to exit: ");
		scanf("%d",&quit);

		if (quit == -1)
		{
			printf("Exiting the sale commission calculator.\n\n");
		}
		
	}
	return 0;
}
