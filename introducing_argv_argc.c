/*Aaron M. Smith
  This program uses argc and argv to average grades
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) //argc is the number of arguments, argv is an array that stores the arguments
{

	if(argc != 6) // ./a.out, first name,last name, grade 1, grade 2, grade 3. argc should be 6. Program will not work if this is not satisfied.
	{
		printf("\nError: Insufficient arguments.\n");
		return 0;
	}

	int grade1 = atoi(argv[3]); //converts array arguments to integers
	int grade2 = atoi(argv[4]);
	int grade3 = atoi(argv[5]);
	int total = grade1+grade2+grade3;
	
	float average = (float)total/3;
	char result;

	if( average >= 90 ) //Sets up conditional statements to assign grade
		result = 'A';
	if( average >= 80 && average < 90 )
	    result = 'B';	
	if( average >= 70 && average < 80 )
		result = 'C';
	if( average >= 60 && average < 70 )
		result = 'D';
	if( average < 60 )
		result = 'F';

	printf("\nThe average total score for the student %s %s is %0.2f and overall grade is %c in the course.\n",argv[1],argv[2],average,result);

	return 0;
}
	
