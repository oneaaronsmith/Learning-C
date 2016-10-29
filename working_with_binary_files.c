/* Aaron M Smith
   Purpose: Working with binary files */

/**********LIBRARIES**********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********DEFINITIONS**********/

typedef struct student{
	int id;
	char name[20];
	float gpa;
} Student;

/********PROTOTYPES*********/

Student findStudent(FILE *fp, int studentId);

Student* getClass(const char* classFile, const char* studentFile, int *len);

/********MAIN********/

int main(int argc, char *argv[])
{

	printf("Is it here?");

	if(argc != 3) //ends program if there are insufficient arguments
	{
		printf("\nInsufficient arguments in command line\n");
		printf("example: ./a.out <class file> <students file>\n ");
		return 0;
	}

	int *length; //initializes integer pointer to store length of array

	printf("Is it here?");
	Student* favorites; 

   	favorites = getClass(argv[1],argv[2],length); //invokes getClass function
	
	return 0;
}
/*********FUNCTIONS**********/

Student findStudent(FILE *fp,int studentID)
{
	Student info;

	fseek(fp,(studentID-1)*sizeof(Student),SEEK_SET);

	fread(&info,sizeof(Student),1,fp);

	if(info.id == 0)
	{
		printf("I'm sorry, but your program hates you.");
	}

	return info;
}

Student* getClass(const char* classFile, const char* studentFile, int* len)
{
	int j = 0; //counter for students;
	
	FILE* filestudent = fopen(studentFile, "rb+"); //open dat file
	
	if(filestudent == NULL)
	{
		printf("\nError: Unable to open file. Your file is a rebel.\n");
		return 0;
	}

	FILE* fileclass = fopen(classFile, "r+"); //open input file

	if(fileclass == NULL)
	{
		printf("Error: unable to open input file.");
		return 0;
	}

	printf("Is it here?");
	fscanf(fileclass,"%d",len); //reads the first input from the .txt as number of students
	printf("%d",*len);

	Student *favorites = malloc(sizeof(struct student)*(*len));
	
	Student *startPtr = favorites;

	for(j = 0; j < *len ; j++)
	{
		int studentID;
		printf("Is it here?");

		fscanf(fileclass,"%d",&studentID);

		Student studentinfo = findStudent(filestudent,studentID);
		(favorites)->id = studentinfo.id;
		(favorites)->gpa = studentinfo.gpa;
		
		printf("\n%d %s %f\n",favorites->id,favorites->name,favorites->gpa);
		favorites++;
	}

	favorites = startPtr;

	return favorites;
}






			

