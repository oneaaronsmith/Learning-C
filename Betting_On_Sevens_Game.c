/*Aaron M Smith
  This program simulates a bet. Two dice will be thrown. The user may guess whether he or she believes the dice will add up to 7, below 7 or above 7.
  If the user is correct, he or she wins. If not, it's a loss.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**************FUNCTION PROTOTYPES**************/

void display_option();

int check_guess(int);

int throw_dice();

int lucky_seven(int,int);

/******************MAIN BEGINS HERE (Is not cut off until end)*************************/

int main(void)
{
	srand(time(NULL));	 		 //Causes a change in the random number generator. Allows use of rand()

	int money, escape, bet,WINS=0,LOSS=0; 	 //introduces necessary variables
	money = 100;				 //sets user's initial money pool to $100
	escape = 0;				 //sets up the choice to escape the game later.

	while (money > 0 && escape != -1)	//sets up necessary while loop to continue playing the game.
	{
/*****************THE USER MAKES A GUESS******************/

	display_option();	 	//Gives the user the display menu for making his or her guess
	
	int x;
	scanf("%d",&x);			//The user selects an option by entering a value for x

		int y;
		y = check_guess(x); 	//The user's guess is sent to a function to be checked. Only 1-3 are valid guesses. 

		while (y != 1)		//If the user did not select a valid value for the guess, a while loop is triggered until a valid option is chosen.
		{
			printf("\nInvalid Choice");
			display_option();
			scanf("%d",&x);
			y = check_guess(x);
		}
	
/******************THE USER MAKES A BET*********************/

	printf("\nYou have $%d to bet. \nHow much $ do you want to bet: ",money);	 //extra credit: requests bet
	scanf("%d",&bet);								 //extra credit: reads in the bet


/*************THE DICE ARE CAST AND RESULTS FOUND***********/

	int DICE, result;

	DICE = throw_dice(); 			 //Calls function: 2 dice are cast and a value is given equal to the sum.

	result = lucky_seven(DICE,x); 	 	 //Calls function: The guess and sum are related to figure out if the user wins the game.

	if(result == 0)				 //The guess was wrong
	{
		printf("\nYou lost. Your guess is incorrect and the dices' sum is %d\n",DICE);
		money = money - bet; 		 //subtracts losses
		LOSS++;
	}

	if(result == 1 && x != 1) 		 //The guess was right. Lucky 7 was not chosen
	{
		printf("\nYou win! Your guess is correct and the dices' sum is %d\n",DICE);
		money = money + bet; 		 //adds winnings
		WINS++;
	}

	if(result == 1 && x == 1) 		 //The guess was right, with Lucky 7 chosen
	{
		printf("\nYOU WIN! Your guess is correct and the dices' sum is %d\n",DICE);
		money = money + bet*3;		 //adds winnings*3 because lucky 7 is special
		WINS++;
	}

/***********CHOICE TO CONTINUE OR LEAVE, DISPLAYS FINAL IF QUIT CHOSEN***************/
	
	printf("\nDo you want to continue or exit? type -1 to exit: ");
	scanf("%d",&escape); 	//If the user requests -1, the while loop will terminate

	if(money <= 0)
		printf("\nYou can't play the game anymore. You have lost all of your money.\n"); //Game ends if money reaches 0

	}

	printf("\nTotal money after playing the game is $%d\n",money);  //Gives the user their total money leftover
	printf("You won %d times and lost %d times\n",WINS,LOSS);  		//Gives a tally for their wins and losses

	return 0;
}


/*******************PROGRAM FUNCTIONS*************************/

void display_option()	//Used to display menu to user
{
	printf("\nEnter your guess (1) Lucky 7 (2) above 7 (3) below 7:\n");
	printf("Please select an option: ");
}

int check_guess(int x)	//Used to check user's intial guess according to menu
{
	if( x < 1 || x > 3)
		return 0;
	else
		return 1;
}

int throw_dice()		//Used to simulate the roll of 2 dice
{
	int x,y,SUM;

	x = 1 + rand() % 6;	//X must be between 1-6
	y = 1 + rand() % 6; //Y must also be between 1-6

	SUM = x + y;		//Sums the dice roll

	return SUM;
}

int lucky_seven(int sum, int guess)	//Used to determine if the user wins the game
{
	int result;
	switch(guess)	//Based on user's choice, the switch checks to see if the user guessed correctly
	{
		case 1:		//User guessed that dice roll would = 7
			if(sum == 7)
				result = 1;
			else
				result = 0;
			break;
		case 2: 	//User guessed that dice roll would be greater than 7
			if(sum > 7)
				result = 1;
			else
				result = 0;
			break;
		case 3: 	//User guessed that dice roll would be less than 7
			if(sum < 7)
				result = 1;
			else
				result = 0;
			break;
	}
	return result;
}
				

//FIN
