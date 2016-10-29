/*Aaron M Smith
  Purpose: Working with structs and enums.*/
  
/*****Libraries*****/

#include <stdio.h>
#include <stdlib.h>

/*****Definitions*****/

//use enum to make working with coin names easier
typedef enum {
	PENNY	= 1,
	NICKEL	= 5,
	DIME	= 10,
	QUARTER	= 25,
} Denomination;

//Use struct where Denomination is the type of coin, quantity is how many*/
typedef struct coin {
	Denomination denomination;
	int quantity;
} Coin;

typedef Coin* PiggyBank;

/*Denomination is the type of coin, quantity is how many*/

/*****Prototypes*****/

PiggyBank loadBank(const char* filename, int* lenPtr);
int totalMoney(PiggyBank bank, int length);
char* enumToString(Denomination denomination);
void printBankToScreen(PiggyBank bank, int length);
void sortByQuantity(PiggyBank bank, int length);
void writeToFile(const char* filename, PiggyBank bank, int length);
PiggyBank minimumChange(int amount);

/*****MAIN*****/

int main(int argc, char* argv[])
{
	//If there are not enough arguments at cmd end program
	if(argc != 3)
	{
		printf("\nInsufficient arguments at command line\n"
			   "Example: ./a.out <input.txt> <output.txt>\n");
		return 0;
	}
	
	//Malloc space for a length pointer
	int length;
	int *lengthPtr = &length;
	
	//Initialize piggybank pointer to get info from loadBank
	PiggyBank bacon;
	bacon = loadBank(argv[1], lengthPtr);
	
	//Print results
	printBankToScreen(bacon,length);

	//Use function to sort by quantity
	sortByQuantity(bacon,length);
	
	//Write sorted function to file
	writeToFile(argv[2],bacon,length);
	
	//Find least amount of change in a value
	//Begin and ask the person for their desired change
	int change;
	printf("\nEnter an amount of change: ");
	scanf("%d",&change);
	
	//Use function to figure out least # of coins needed.
	PiggyBank bonusbank;
	bonusbank = minimumChange(change);
	
	//Print information
	printf("%d cents can be made with:"
		   "\n%d quarters"
		   "\n%d dimes"
		   "\n%d nickels"
		   "\n%d pennies\n",change, bonusbank[0].quantity,bonusbank[1].quantity,bonusbank[2].quantity,bonusbank[3].quantity);
	
	//push the new command line farther away:
	printf("\n");
	
	//Let freedom ring
	free(bacon);
	free(bonusbank);
	
	//FIN
	return 0;
}

//*****FUNCTIONS*****//

PiggyBank loadBank(const char* filename, int* length) //Loads coin information from .txt file
{
	//Open file for reading and make sure it succeeds
	FILE* fp = fopen(filename,"r");
	
	if(fp == NULL)
	{ 
		printf("Error, could not open file %s",filename);
		return NULL;
	}
	
	//Get the length of the array
	fscanf(fp, "%d", length);
	
	//Initialize pointer and malloc appropriate space
	PiggyBank bacon;
	bacon = malloc(sizeof(Coin)*(*length));
	
	//Load data from file
	int i;
	for(i = 0 ; i < *length ; i++)
	{
	fscanf(fp,"%u %d",&bacon[i].denomination,&bacon[i].quantity);
	}
	
	//Close file and return results
	fclose(fp);
	return bacon;
}

int totalMoney(PiggyBank bank, int length)
{
	//Initialize the initial amount of money
	int money = 0;
	
	//Add money depending on each part of the array.
	int i;
	for(i = 0; i < length ; i++)
	{	
		switch(bank[i].denomination)
		{
			case PENNY :
			money += 1*bank[i].quantity;
			break;
			
			case NICKEL :
			money += 5*bank[i].quantity;
			break;
			
			case DIME :
			money += 10*bank[i].quantity;
			break;
			
			case QUARTER :
			money += 25*bank[i].quantity;
			break;
		}
	}
	
	//Return total.
	return money;
}

char* enumToString(Denomination denomination)
{	
	//make a string depending on type of denomination
	switch(denomination)
	{
		case PENNY :
		return "penny";
		break;
		
		case NICKEL :
		return "nickel";
		break;
		
		case DIME :
		return "dime";
		break;
		
		case QUARTER :
		return "quarter";
		break;
		
		default :
		return "sadface";
		break;
	}
	
}

void printBankToScreen(PiggyBank bank, int length)
{
	//First, find the total money in bank and print that
	int total;
	total = totalMoney(bank,length);
	printf("\nYou have %d cents in your piggy bank\n",total);
	
	//Print bank information and substitute coin name for denomination
	int i;
	char* name;
	for( i = 0; i < length ; i++)
	{
		name = enumToString(bank[i].denomination);
		printf("%s %d\n",name,bank[i].quantity);
	}
	
}

void sortByQuantity(PiggyBank bank, int length) //sort bank by insertion. 
{
	Coin insert; //for holding insertion element
	int i; //for looping
	for(i = 1; i < length ; i++)
	{
		//Set up locations and holders
		int move = i;
		insert = bank[i];
	
		//Find the insertion point
		while(move > 0 && bank[move -1].quantity > insert.quantity)
		{
			bank[move] = bank[move - 1];
			--move;
		}
		
		//Place the insertion
		bank[move] = insert;
	}
}

void writeToFile(const char* filename, PiggyBank bank, int length) //write bank to output file
{
	//Open file for writing
	FILE* fp = fopen(filename,"w");
	
	//Announce if open failed
	if(fp == NULL)
	{
		printf("Error, could not open file %s",filename);
		return;
	}
	
	//Print length of array
	fprintf(fp,"%d\n",length);
	
	//Print informaiton
	int i;
	for(i = 0; i < length ; i++)
	{
		fprintf(fp,"%d %d\n",bank[i].denomination,bank[i].quantity);
	}
	
	//Close the file
	fclose(fp);
}

PiggyBank minimumChange(int amount)
{
	int check;
	int update = amount;
	
	//Malloc space for new bank pointer. Length is 4.
	PiggyBank ham;
	ham = malloc(sizeof(Coin)*4);
	
	//Because we are not reading from a file, initial bank info is provided.
	ham[0].denomination = QUARTER;
	ham[1].denomination = DIME;
	ham[2].denomination = NICKEL;
	ham[3].denomination = PENNY;
	
	//Find number of quarters and update value
	if(amount/QUARTER != 0)
	{
		check = amount/QUARTER;
		ham[0].quantity = check;
		update = amount % QUARTER;
	}
	else
		ham[0].quantity = 0;
	
	//Find number of dimes and update value
	if(update/DIME != 0)
	{
		check = update/DIME;
		ham[1].quantity = check;
		update = update % DIME;
	}
	else
		ham[1].quantity = 0;
	
	//Find number of nickels and update value
	if(update/NICKEL != 0)
	{
		check = update/NICKEL;
		ham[2].quantity = check;
		update = update % NICKEL;
	}
	else
		ham[2].quantity = 0;
	
	//Find number of nickels and update value
	if(update/PENNY != 0)
	{
		check = update/PENNY;
		ham[3].quantity = check;
		update = update % PENNY;
	}
	else
		ham[3].quantity = 0;
	
	//Return pointer
	return ham;
}
