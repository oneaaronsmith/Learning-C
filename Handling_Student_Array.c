/*Aaron M. Smith
  This program involves the use of conditional statements and arrays in functions to handle
  a student.*/

#include <stdio.h>
#include <stdlib.h>

//Macros are made to specify size of arrays. Needed to make prototypes for processing
#define BILLROWS 6 //Made to store info for 6 students
#define BILLCOLUMNS 3 //tuition,scholarship,fixedtuition
#define STUDENTROWS 6 //Made to store info for 6 students
#define STUDENTCOLUMNS 2 //student ID and student type

/********************FUNCTION PROTOTYPES********************/

int checkID(int stuInfo[STUDENTROWS][STUDENTCOLUMNS],int idEntered);

void processUndergrad(float billInfo[BILLROWS][BILLCOLUMNS],int id,int rowNumber);

void processGraduate(float billInfo[BILLROWS][BILLCOLUMNS],int id,int rowNumber);

void processPhD(float billInfo[BILLROWS][BILLCOLUMNS],int id, int rowNumber);

int checkHours(int hours, int type);

void processFinalReport(int stuInfo[STUDENTROWS][STUDENTCOLUMNS], float billInfo[BILLROWS][BILLCOLUMNS]);

void processReportStudents(int stuInfo[STUDENTROWS][STUDENTCOLUMNS], float billInfo[BILLROWS][BILLCOLUMNS]);

/********************MAIN BEGINS HERE********************/

int main(void)
{
/*The entire program is based on certain starting student information. The information
  for six students will be included. Also an array is made to keep bill information.*/
	
	int stuInfo[STUDENTROWS][STUDENTCOLUMNS]={  {394003920,2}, //{Student number, student type}
					  							{388920394,3},
					  							{499230076,1},
					  							{298760112,2},
					  							{592493811,3},
					  							{355982306,3} };

	float billInfo[BILLROWS][BILLCOLUMNS]={ 	{0.0,0.0,0.0}, //(tuition,scholarship discount,net tuition)
   									 			{0.0,0.0,0.0},
									 			{0.0,0.0,0.0},
									 			{0.0,0.0,0.0},
									 			{0.0,0.0,0.0},
									 			{0.0,0.0,0.0} };

//The program will allow multiple students' info to be recorded. A while statement is set up to allow continuation:
	int option = 1;
	while(option != 0)
	{
	//The program begins by asking the user for an ID:

		int idEntered;
		printf("\nEnter the student ID: ");
		scanf("%d",&idEntered);

	/*The program determines if the ID is valid using a function. If the id is valid, the
  	program will return the row denotation for use in further functions.*/

		int rowID;
		rowID = checkID(stuInfo, idEntered);

		while(rowID == -1)
		{
			printf("Invalid Student ID. Please type again: ");
			scanf("%d",&idEntered);
			rowID = checkID(stuInfo, idEntered);
		}

	/*There are 3 different student types. Depending on the student, there will be
	  different costs associated with their account. So, it is necessary to invoke
	  separate functions depending on the student. The following switch statement will
	  make sure the proper function is used.*/

		switch(stuInfo[rowID][1])
		{
			case 1:
				processUndergrad(billInfo,idEntered,rowID); //Type 1 students are undergraduates
				break;
			case 2:
				processGraduate(billInfo,idEntered,rowID);	//Type 2 students are graduates
				break;
			case 3:
				processPhD(billInfo,idEntered,rowID);		//Type 3 students are Phd
				break;
		}

	//The continue option is issued:
		printf("\nDo you want to continue for the next student? If yes hit 1 else hit 0: ");
		scanf("%d",&option);
	}

	processFinalReport(stuInfo,billInfo); //This function prints a summary of the student info recorded

	printf("\n\n**********BONUS PART: SORT BY STUDENT ID**********\n");

	processReportStudents(stuInfo,billInfo); //This function prints a summary that has been sorted according to ascending student IDs

	return 0;
}

/*************************FUNCTIONS*************************/

int checkID(int stuInfo[][STUDENTCOLUMNS],int ID) //This function checks to make sure the ID is valid. IDs are stored in stuInfo array.
{
	int row, rowresult;

	rowresult = -1; //Makes a default in case the ID is invalid

	for (row = 0; row < 6; row++)
		{
			if(stuInfo[row][0] == ID)
				rowresult = row;
		}
	
	return rowresult;
}

int checkHours(int hours, int type) //Checks to make sure student is enrolled in a correct amount of class hours
{
	int result = 0; //Default is set to improper number of hours

	switch(type)
	{
		case 1: //undergraduate students need to be enrolled in at least 3, no more than 18
			if(hours >= 3 && hours <= 18)
				result = 1;
			break;
		case 2: //graduate, no more than 12 hours
			if(hours >= 3 && hours <= 12)
				result = 1;
			break;
		case 3: //PhD, no more than 9 hours
			if(hours >=3 && hours <= 9)
				result = 1;
			break;
	}

	return result;
}

int checkScholarship(float tuition, float scholarship, int type) //Checks to make sure a valid scholarship amount is chosen.
{
	int result = 0;
	float maximum;

	switch(type)
	{
		case 1: //Undergraduates eligible for scholarship 50% of tuition
			maximum = tuition/2;
			if(scholarship <= maximum)
				result = 1;
			break;
		
		case 2: //Graduates eligible for scholarship 75% of tuition
			maximum = tuition*0.75;
			if(scholarship <= maximum)
				result = 1;
			break;

		case 3: //PhD eligible for $10000 stipend
			maximum = 10000.00;
			if(scholarship <= maximum)
				result = 1;
			break;
	}
	
	return result;
}

void processUndergrad(float billInfo[][BILLCOLUMNS],int ID, int rowID)
{
	int hours,hourcheck,scholarcheck;
	float tuition,scholarship,fixedtuition;

	//The function asks for enrollment hours:
	printf("\nEnter the number of credit hours: \n");
	scanf("%d",&hours);

	hourcheck = checkHours(hours,1);
	
	while(hourcheck != 1) //Hours must be valid
	{
		printf("\nUndergrad students must be enrolled in 3-18 hours. Enter again: \n");
		scanf("%d",&hours);
		hourcheck = checkHours(hours,1);
	}

	//The function calculates tuition for the student based on hours:
	tuition = 750*(float)hours;

	//The function asks for scholarship amount:
	printf("\nEnter Scholarship amount: $");
	scanf("%f",&scholarship);

	//The function determines if it is valid. If not, repeats question:
	scholarcheck = checkScholarship(tuition,scholarship,1);

	while(scholarcheck != 1)
	{
		printf("\nScholarship can't be greater than 50 percent the tuition. Enter the correct amount again: \n$");
		scanf("%f",&scholarship);
		scholarcheck = checkScholarship(tuition,scholarship,1);
	}

	//Calculate the bill with scholarship:
	fixedtuition = tuition - scholarship;

	//The information will be kept in the bill array:
	billInfo[rowID][0] = tuition;
	billInfo[rowID][1] = scholarship;
	billInfo[rowID][2] = fixedtuition;

	//The information will be printed:
	printf("\nUndergrad Student %d Tuition is :\n",ID);
	printf("Gross					$ %0.2f \n",tuition);
	printf("Stipend Amount				$ %0.2f \n",scholarship);
	printf("Total Tuition Bill			$ %0.2f \n",fixedtuition);

}

void processGraduate(float billInfo[][BILLCOLUMNS], int ID,int rowID)
{
	int hours, hourcheck,scholarcheck;
	float tuition,scholarship,fixedtuition;

	//The function asks for enrollment hours
	printf("\nEnter the number of credit hours: \n");
	scanf("%d",&hours);

	//The function determines if hours are valid
	hourcheck = checkHours(hours,2);

	while( hourcheck != 1)
	{
		printf("\nGrad students must be enrolled in 3-12 hours. Enter again: \n");
		scanf("%d",&hours);
		hourcheck = checkHours(hours,2);
	}
	
	//The function calculates tuition for the student:
	tuition = 1000*(float)hours;

	//The function asks for scholarship amount
	printf("\nEnter Scholarship amount: $");
	scanf("%f",&scholarship);

	//The function determines if the scholarship is valid
	scholarcheck = checkScholarship(tuition,scholarship,2);

	while( scholarcheck != 1)
	{
		printf("\nScholarship can't be greater than 75 percent the tuition. Enter the correct amount again: \n$");
		scanf("%f",&scholarship);
		scholarcheck = checkScholarship(tuition,scholarship,2);
	}

	//The function calculates fixed tuition bill
	fixedtuition = tuition - scholarship;

	//The function stores info in bill array
	billInfo[rowID][0] = tuition;
	billInfo[rowID][1] = scholarship;
	billInfo[rowID][2] = fixedtuition;

	//The function prints info
	printf("\nGraduate student %d Tuition is :\n",ID);
	printf("Gross					$ %0.2f \n",tuition);
	printf("Scholarship Amount			$ %0.2f \n",scholarship);
	printf("Total Tuition Bill			$ %0.2f \n",fixedtuition);

}
		
void processPhD(float billInfo[][BILLCOLUMNS],int ID, int rowID)
{
	int hours, hourcheck, scholarcheck;
	float tuition,scholarship,fixedtuition;

	//The function asks for hours enrolled:
	printf("\nEnter the number of credit hours: \n");
	scanf("%d",&hours);

	//The function determines if hours are valid:
	hourcheck = checkHours(hours,3);

	while( hourcheck != 1)
	{
		printf("PhD students must be enrolled in 3-9 hours. Enter again: \n");
		scanf("%d",&hours);
		hourcheck = checkHours(hours,3);
	}

	//The function calculates tuition for the student based on hours:
	tuition = 1200*(float)hours;
	//The function asks for scholarship amount:
	printf("\nEnter stipend amount: $");
	scanf("%f",&scholarship);

	//The function determines if scholarship is valid:
	scholarcheck = checkScholarship(tuition,scholarship,3);

	while(scholarcheck != 1)
	{
		printf("\nStipend can't be greater than $10000. Enter correct amount: \n$");
		scanf("%f",&scholarship);
		scholarcheck = checkScholarship(tuition,scholarship,3);
	}

	//The function calculates fixed tuition bill:
	fixedtuition = tuition - scholarship;

	//The function stores info in bill array:
	billInfo[rowID][0] = tuition;
	billInfo[rowID][1] = scholarship;
	billInfo[rowID][2] = fixedtuition;

	//The function prints info:
	printf("\nPhd Student %d Tuition is: \n",ID);
	printf("Gross					$ %0.2f \n",tuition);
	printf("Stipend					$ %0.2f \n",scholarship);
	printf("Total Tuition Bill			$ %0.2f \n",fixedtuition);
}

void processFinalReport(int stuInfo[][STUDENTCOLUMNS],float billInfo[][BILLCOLUMNS]) //This function bubble sorts both arrays according to student type. It also prints the info.
{
	int pass, row, holdstudent0,holdstudent1;   	//Initializes needed integers
	float	holdbill0,holdbill1,holdbill2;			//Initializes needed float variables.
	
	for (pass = 1; pass < STUDENTROWS; pass++)  	//Creates the pass for bubble sorting.
	{
		for(row = 0; row < STUDENTROWS - 1; row++)
		{
			if(stuInfo[row][1] > stuInfo[row+1][1]) // rearranged according to student type, the following bubble sort works to sort array for all columns and both arrays.
			{
				holdstudent0 = stuInfo[row][0]; 	//Holds allow the function to rearrange data.
				holdstudent1 = stuInfo[row][1];
				holdbill0 = billInfo[row][0];
				holdbill1 = billInfo[row][1];
				holdbill2 = billInfo[row][2];
				stuInfo[row][0] = stuInfo[row+1][0];
				stuInfo[row][1] = stuInfo[row+1][1];
				stuInfo[row+1][0] = holdstudent0;
				stuInfo[row+1][1] = holdstudent1;
				billInfo[row][0] = billInfo[row+1][0];
				billInfo[row][1] = billInfo[row+1][1];
				billInfo[row][2] = billInfo[row+1][2];
				billInfo[row+1][0] = holdbill0;
				billInfo[row+1][1] = holdbill1;
				billInfo[row+1][2] = holdbill2;
			}
		}
	}
	
	//**********The final purpose of the function is to print and total the student information**********:
	float totalgross = 0.0,totalscholar = 0.0,totalnet = 0.0; //Assigns float variables so that a total can be calculated

	printf("\nSTUDENT BILLING REPORT\n\n\n"); 			  //Begins the printing of student data
	printf("\nSTUDENT	   	TYPE		GROSS		SCHOLARSHIP		NET\n");
	for(row = 0; row < STUDENTROWS ; row++)
	{
		if(billInfo[row][0] != 0) //If a student's info was not entered, he or she is left out of the final report
		{
			printf("%d%10d%20.2f%20.2f%16.2f\n",stuInfo[row][0],stuInfo[row][1],billInfo[row][0],billInfo[row][1],billInfo[row][2]);
		}

		totalgross = totalgross + billInfo[row][0]; 	//Totals gross tuition
		totalscholar = totalscholar + billInfo[row][1]; //Totals scholarship money
		totalnet = totalnet + billInfo[row][2]; 		//Totals fixed tuition
	}
	printf("				-------------------------------------------\n");
	printf("TOTAL:%33.2f%20.2f%16.2f\n",totalgross,totalscholar,totalnet); //Final print
}

void processReportStudents(int stuInfo[][STUDENTCOLUMNS],float billInfo[][BILLCOLUMNS]) //BONUS: This function bubble sorts both arrays according to student ID. It also prints the info.
{
	int pass, row, holdstudent0,holdstudent1;   	//Initializes needed integers
	float	holdbill0,holdbill1,holdbill2;			//Initializes needed float variables.
	
	for (pass = 1; pass < STUDENTROWS; pass++)  	//Creates the pass for bubble sorting.
	{
		for(row = 0; row < STUDENTROWS - 1; row++)
		{
			if(stuInfo[row][0] > stuInfo[row+1][0]) // rearranged according to student ID, the following bubble sort works to sort array for all columns and both arrays.
			{
				holdstudent0 = stuInfo[row][0]; 	//Holds allow the function to rearrange data.
				holdstudent1 = stuInfo[row][1];
				holdbill0 = billInfo[row][0];
				holdbill1 = billInfo[row][1];
				holdbill2 = billInfo[row][2];
				stuInfo[row][0] = stuInfo[row+1][0];
				stuInfo[row][1] = stuInfo[row+1][1];
				stuInfo[row+1][0] = holdstudent0;
				stuInfo[row+1][1] = holdstudent1;
				billInfo[row][0] = billInfo[row+1][0];
				billInfo[row][1] = billInfo[row+1][1];
				billInfo[row][2] = billInfo[row+1][2];
				billInfo[row+1][0] = holdbill0;
				billInfo[row+1][1] = holdbill1;
				billInfo[row+1][2] = holdbill2;
			}
		}
	}
	
	//**********The final purpose of the function is to print and total the student information**********:
	float totalgross = 0.0,totalscholar = 0.0,totalnet = 0.0; //Assigns float variables so that a total can be calculated

	printf("\nSTUDENT BILLING REPORT (SORTED BY STUDENT ID)\n\n"); 			  //Begins the printing of student data
	printf("\nSTUDENT	   	TYPE		GROSS		SCHOLARSHIP		NET\n");
	for(row = 0; row < STUDENTROWS ; row++)
	{
		if(billInfo[row][0] != 0) //If a student's info was not entered, he or she is left out of the final report
		{
			printf("%d%10d%20.2f%20.2f%16.2f\n",stuInfo[row][0],stuInfo[row][1],billInfo[row][0],billInfo[row][1],billInfo[row][2]);
		}

		totalgross = totalgross + billInfo[row][0]; 	//Totals gross tuition
		totalscholar = totalscholar + billInfo[row][1]; //Totals scholarship money
		totalnet = totalnet + billInfo[row][2]; 		//Totals fixed tuition
	}
	printf("				-------------------------------------------\n");
	printf("TOTAL:%33.2f%20.2f%16.2f\n",totalgross,totalscholar,totalnet); //Final print
}

