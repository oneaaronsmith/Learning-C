/*Aaron M. Smith
  Purpose: A quick review of common C concepts. Reading from a file. Finding minimums and maximums in an array. Writing to a file.
*/

/**********LIBRARIES********************/

#include <stdio.h>
#include <stdlib.h>

/**********FUNCTION PROTOTYPES**********/

double* read_file(char *filename, int length);

double find_min(double *array, int length);

double find_max(double *array, int length);

double find_avg(double *array, int length);

void write_to_file(char *filename, double *array, int length);

/**********MAIN*************************/

int main(int argc, char *argv[]) //input length and filename at command line
{
	/*
	   This program requires input from the command prompt. There should be a length,
	    an input file, and an output file for arrays as follows:
	   argv[0] = ./a.out
	   argv[1] = length (5)
	   argv[2] = input.txt
	   argv[3] = output.txt
	*/
	
	if(argc != 4) //There needs to be a certain number of arguments at the command line.
	{
		printf("Incorrect Usage.");
		printf("\nPlease input length, input file name, and output file name at command line.");
		printf("\n ./a.out <file length> <input.txt> <output.txt>\n");
		return 0;
	}

	int length = atoi(argv[1]); //converts the string in the command line to an integer

	double *filedata = read_file(argv[2],length); //invokes read_file

	if (filedata == 0) //If the file was unable to open, filedata will be 0
	{
		printf("\nUnable to open the input file %s\n",argv[2]);
		return 0;
	}
	
	double min = find_min(filedata,length) ;
	double max = find_max(filedata,length) ;
	double average = find_avg(filedata,length);

	printf("min: %lf\nmax: %lf\navg: %lf",min,max,average); //prints important data

	write_to_file(argv[3],filedata,length); //invokes write_to_file function

	printf("\n"); //line of separation

	free(filedata);

	return 0;
}

/**********FUNCTIONS******************/

double* read_file(char *filename, int length) //This function opens the file and puts the info in a pointer
{
	FILE* file = fopen(filename, "r");  //opens the input.txt file for reading

	if (file == NULL) //IF the file is unable to open, it is NULL and the function returns 0
	{
		return 0;
	}

	int i = 0; //creates a counter
	double value; //to be used as the number in the array
	double *ptr;  //to be filled with knowledge
	ptr = malloc(sizeof(double)*length); //malloc space for the pointer

	for(i = 0; i < length ; i++) 	   //Each value in the input.txt file is put into the pointer
	{
		fscanf(file,"%lf",&value);

		*(ptr+i) = value;
	}
	
	fclose(file); //closes file
	return ptr;
}

double find_min(double* array, int length) //This function finds the minimum number in the array
{
	int i = 0;
	double minimum = *array;

	for(i = 0; i < length ; i++)
	{
		if(minimum > *(array+i)) //if the min is greater than the next #, it is replaced
			minimum = *(array+i);
	}

	return minimum;
}

double find_max(double* array, int length) //this function finds the maximum number in the array
{
	int i = 0;
	double maximum = *array;

	for(i = 0; i < length ; i++)
	{
		if(maximum < *(array+i)) //if the max is less than the next # in the array, it is replaced
		   maximum = *(array+i);
	}
	
	return maximum;
}

double find_avg(double* array, int length) //this functino returns the average of the array values
{
	int i = 0;
	double sum = 0;

	for(i = 0; i < length ; i++)
	{
		sum+= *(array+i); 				 //sums the array values
	}

	double average = sum/(double)length; //averages the array values

	return average;
}

void write_to_file(char *filename,double *array, int length) //This function writes the info to an ouput file
{
	FILE* writefile = fopen(filename,"w");

	if(writefile == NULL)
	{
		printf("Unable to open an output file");
		return;
	}

	int i;
	for(i = length-1; i > -1 ; i--) //prints array in reverse order (lab instructions)
	{
		fprintf(writefile,"%g\n",*(array+i));
	}
	
	fclose(writefile);
}

