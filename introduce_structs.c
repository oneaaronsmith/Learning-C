/*Aaron M Smith
  The purpose of this program is to introduce working with structs. 
 */

/**********LIBRARIES*******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********DEFINITIONS*****************/

//Define a struct of type song
typedef struct song {
	char* name;
	int rating;
	int numTimesPlayed;
} Song;

#define MAXNAMESIZE 20 //Largest valid size of a song name.

/**********FUNCTION PROTOTYPE**********/

Song* readAlbum(const char* filename, int* lenPtr);

void printAlbum(Song* album, int len);

int changeRating(char* title, int rating, Song* album, int len);

int listenToSong(char* title, Song* album, int len);

void bubble_sort(Song* album, int len);

/**********MAIN************************/

int main(int argc, char *argv[])
{
	/*
	  This program requires input at the command line. The command should include the following:
	  argv[0] : ./a.out
	  argv[1] : input.txt file
	*/

	if(argc != 2) //If there are insufficient arguments at the command line, the program ends
	{
		printf("\nInsufficient arguments at command line.\n");
		printf("Example: ./a.out <input file name>\n");
		return 0;
	}

	int *lengthPtr = malloc(sizeof(int)); //Introduces a pointer for the length of the struct array

	Song* songinfo = readAlbum(argv[1], lengthPtr); //Invokes the readAlbum function

	int len = *lengthPtr;

	printAlbum(songinfo, len); //prints album information

	int choice = -1;
	int newrating; //Holds new rating
	int newratingindex; //Will be given the index of the song with a changed rating
	int newsongindex;	//Will be given the index of the song that is played
	char* songchoice = malloc(sizeof(char)*MAXNAMESIZE); //Will hold the song choice

	while(choice != 0) //will loop a menu until a proper choice is satisfied.
	{
	printf("\nEnter 1 to listen to a song.\nEnter 2 to change a rating.\nEnter 0 to quit.\n Choice: ");
	scanf("%d",&choice);
	
	switch(choice) //Different outcomes depending on menu choices.
	{
		case 0 : //Exit choice
			printf("\ngoodbye\n");
			break;
		
		case 1 : //Triggers if the user decides to listen to a song
			printf("Enter a title: ");
			scanf("%s",songchoice);
			newsongindex = listenToSong(songchoice,songinfo,len); //invokes listenToSong function
			if(newsongindex != -1)
			  printf("\n%s %d %d\n",(songinfo+newsongindex)->name,(songinfo+newsongindex)->rating,(songinfo+newsongindex)->numTimesPlayed);
			break;

		case 2: //Triggers if the user wants to change a song rating
			printf("Enter a title: ");
			scanf("%s",songchoice);
			printf("Enter a new rating: ");
			scanf("%d",&newrating);
			newratingindex = changeRating(songchoice,newrating,songinfo,len); //invokes changeRating function
			if(newratingindex != -1)
			  printf("\n%s %d %d\n",(songinfo+newratingindex)->name,(songinfo+newratingindex)->rating,(songinfo+newratingindex)->numTimesPlayed);
			break;
	}
	}

	printf("\n\n*Bubble Sort*\n\n");
	
	bubble_sort(songinfo,len); //Invokes bubble sort to sort by number of times played
	printAlbum(songinfo,len);  //Prints sorted struct

	//*****For the sake of FREEDOM:

	int i = 0; //Creates a counter for free() function
	Song* start = songinfo; //Keeps the beginning address intact

	for(i = 0; i < *lengthPtr ; i++) //This for loop frees the character pointers
	{
		free(songinfo->name);
		songinfo++;
	}

	songinfo = start; //reset the address to the beginning

	free(songchoice);//Free the name malloc
	free(songinfo);  //Free the structure malloc
	free(lengthPtr); //Free the integer malloc
	

	return 0;
}
	


/**********FUNCTIONS**********/

Song* readAlbum(const char* filename, int* lenPtr) //Reads info from a file to a struct. DOES NOT NEED TO BE CHANGED FROM PRELAB 2
{
	FILE *file = fopen(filename, "r"); //opens the input.txt for reading

	if(file == NULL) //Ends the function if file does not open properly
	{
		printf("\nUnable to open file %s\n",filename); //If 
		return 0;
	}

	fscanf(file,"%d",*&lenPtr); //Reads the first input from the .txt as the length

	int i = 0; //counter
	
	Song *songinfo = malloc(sizeof(struct song)*(*lenPtr)); //mallocs struct space

	if(songinfo == NULL)
	{
		printf("Failed to allocate space to struct.\n");
	}

	Song *startsong = songinfo; //keeps track of initial address

	for(i = 0; i < *lenPtr ; i++) //this loop assigns values to the struct from the .txt
	{
		songinfo->name = malloc(sizeof(char)*MAXNAMESIZE);
		fscanf(file,"%s",songinfo->name); //could also use (*(songinfo+i)).name
		fscanf(file,"%d",&songinfo->rating);
		fscanf(file,"%d",&songinfo->numTimesPlayed);
		++songinfo;
	}

	songinfo = startsong; //reset address
	fclose(file); //closes file

	return songinfo; //returns the Song*
}

void printAlbum(Song* album, int len) //this function prints the information held in the struct
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		printf("%s %d %d\n",(*(album+i)).name,(*(album+i)).rating,(*(album+i)).numTimesPlayed); //Could also use -> notation
	}
}

int changeRating(char* title, int rating, Song* album, int len) //This function allows user to change song rating
{
	int i = 0;
	int equality;

	for(i = 0; i < len; i++)
	{
		equality = strncmp(title,(album+i)->name,MAXNAMESIZE); //searches for name of song in index
		if(equality == 0)
		{
			(album+i)->rating = rating;
			return i;
		}
	}

	printf("Unable to find %s\n\n",title); //If song does not exist, user cannot change rating
	return -1;
			
}

int listenToSong(char *title, Song* album, int len) //lets user listen to song (adds to number of times played)
{
	int i = 0; //counter
	int equality; //important

	for(i = 0; i < len; i++)
	{
		equality = strncmp(title,(*(album+i)).name,MAXNAMESIZE); //finds song in index
		if(equality == 0)
		{
			(album+i)->numTimesPlayed = (album+i)->numTimesPlayed + 1;
			return i;
		}
	}

	printf("Unable to find %s\n\n",title); //will only print if there was no match
	return -1;
}

void bubble_sort(Song* album, int len) //sorts album by # of times played
{
	int i; //will act as a counter
	int j; //will act as a bubble
	char *holdname = malloc(sizeof(char)*MAXNAMESIZE); //creates a hold for the name of the song
	int holdrating,holdnum; //creates holds for rating and # of times played

for( j = 0; j < len ; j++) //BUBBLE SORTING
{
	for(i = 0; i < len - 1 ; i++)
	{
		if( (album+i)->numTimesPlayed >= (album+i+1)->numTimesPlayed )
		{
			holdname = (album+i)->name;
			holdrating = (album+i)->rating;
			holdnum = (album+i)->numTimesPlayed;

		    (album+i)->name = (album+i+1)->name;
			(album+i)->rating = (album+i+1)->rating;
			(album+i)->numTimesPlayed = (album+i+1)->numTimesPlayed;

			(album+i+1)->name = holdname;
			(album+i+1)->rating = holdrating;
			(album+i+1)->numTimesPlayed = holdnum;
		}
	}
}
}

