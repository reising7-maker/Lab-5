/*
Levi Reising
Computer Science
*/


#include <iostream>
#include <stdlib.h>
#include <time.h>

/*Allows the user to set up how many attempts they would like per game
Precondition:
- The user enters a number for how many attempts they want.

Postcondition:
- The number of attempts is set between 1 and max.
- Repeat is reset to 2 so the user must choose whether to play again.*/
void setup(int& repeat, int& attemptsNum, int& max);


/*The section where the user guesses the number
Precondition:
- The number of attempts was created by setup().
- A random number must be generated between 0 and 100.

Postcondition:
- The user has used all their attempts or guessed the correct number.
- The final guess and random number are available to the next void to use.*/
void guesses(int attempts, int attemptsNum, int& guessNum, int& ranNum, int max);


/*Counts the number of wins and losses the user has obtained.
Precondition:
- The user must have finished guessing.
- The final guess and random number must be available.

Postcondition:
- The user's win or loss is determined.
- The appropriate win or loss counter is increased by one.*/
void counter(int& losses, int& wins, int guessNum, int ranNum);


/*Gives the user the option to play again.
Precondition:
- A game must have finished.
- The user must be asked whether they want to play again.

Postcondition:
- Repeat is set to 1 if the user wants to play again.
- Repeat is set to 0 if the user wants to quit.
- Invalid answers are deleted and question is asked again.*/
void again(int& repeat);


/*Displays how many times you won and lost.
Precondition:
- The total number of wins and losses variables must be done.

Postcondition:
- The total wins and losses are displayed to the user.*/
void WtoL(int wins, int losses);


/*The void functions below this will be inside other void functions.
Precondition:
- The user's guess must be lower/higher than the random number.

Postcondition:
- One random message indicating that the guess was too low/high is displayed.*/
void incorrectLow();
void incorrectHigh();


/*This displays 10 different statements based on if you won or lost
Precondition:
- The user must have/(have not) guessed the correct number.

Postcondition:
- One random winning/losing message is displayed.*/
void win();
void lose();


/*These give 5 different play again statements each for if you won or lost.
Precondition:
- The user must have won or lost the previous game.

Postcondition:
- One random message asking to play again is displayed.*/
void replayW();
void replayL();


using namespace std;

int main()//--------------------------------------------------------------------------------------------------------------------------------------
{
	//Giving seeds for the future random numbers
	srand(time(NULL));

	//Creating variables
	int ranNum = 0;
	int guessNum = 0;
	int attempts = 0;
	int attemptsNum = 0;
	int repeat = 2;
	int losses = 0;
	int wins = 0;
	int max = 20;

	cout << "You will need to pick a number from 0-100" << endl;
	cout << "Just know, if the goblin talks to you, do the opposite of what it says \n" << endl;
	//This allows them to play the game multiple times
	do
	{
		setup(repeat, attemptsNum, max);				
		guesses(attempts, attemptsNum, guessNum, ranNum, max);		
		counter(losses, wins, guessNum, ranNum);		
		again(repeat);

	} while (repeat == 1);

	WtoL(wins, losses);
	return 0;
}

//Repeat is changed from whatever it was before, to 2 so it needs &.
//AttemptsNum will be used later on in other functions, so it also needs &.
void setup(int& repeat, int& attemptsNum, int& max)//-------------------------------------------------------------------------------------------------------
{
	//Forces them to change repeat to 1 or 0 at the end.
	repeat = 2;

	cout << "How many attempts would you like? (Max of " << max << "): ";
	cin >> attemptsNum;

	//If what they entered isnt a number
	while (cin.fail())
	{
		//Gets rid of the error state
		cin.clear();
		//Gets rid of the characters that caused the error (up to one million characters) until it reaches a white space character. 
		cin.ignore(1000000, '\n');

		cout << "Must be a number!: ";
		cin >> attemptsNum;
	}

	//If they pick a number bigger than the max, it changes to the max
	if (attemptsNum > max)
	{
		cout << "Well you're only getting" << max << endl;
		attemptsNum = max;
	}
	else if (attemptsNum < 1)
	{
		//They get a random number between 1-max if they pick a number less than 1
		cout << "Really? You're playing if you want to or not. Since you wont pick I will. You're getting " ;
		attemptsNum = rand() % max + 1;
		cout << attemptsNum << " attempts." << endl;
		
	}
}

//Attempts wont be used later so it wont need &.
//AttemptsNum will be used later, but will be changed, so it doesnt need &.
//guessNum and ranNum will be used so it needs &.
void guesses(int attempts, int attemptsNum, int& guessNum, int& ranNum, int max)//------------------------------------------------------------------------
{
	//Creates a random number before the loop begins so the number stays the same
	ranNum = rand() % 101;
	for (attempts = 0; attempts < attemptsNum; attempts++)
	{
		cout << "Whats your guess?: ";
		cin >> guessNum;
		while (cin.fail())
		{
			//Gets rid of the error state
			cin.clear();
			//Gets rid of the characters that caused the error (up to one million characters) until it reaches a white space character. 
			cin.ignore(1000000, '\n');

			cout << "Must be a number!: ";
			cin >> guessNum;
		}
		if (guessNum == ranNum)
		{
			attempts = attempts + max;
		}
		else if (guessNum > ranNum && attempts != attemptsNum - 1)
			//If they have one more try, it wont say if its too low/high
		{
			incorrectHigh();
			cout << "\n";
		}
		else if (guessNum < ranNum && attempts != attemptsNum - 1)
		{
			incorrectLow();
			cout << "\n";
		}
	}
}

//Losses and wins will need to be used later from this so it needs &.
//guessNum and ranNum wont be used later and will get changed, so it doesnt need &.
void counter(int& losses, int& wins, int guessNum, int ranNum)//---------------------------------------------------------------------------------
{
	if (guessNum != ranNum)
		{
			lose();
			cout << "The number was: " << ranNum << ".";
			losses++;
			replayL();
		}
		else
		{
			win();
			wins++;
			replayW();
		}
}

//Repeat will need to be used to continue the loop, so i needs &.
void again(int& repeat)//--------------------------------------------------------------------------------------------------------------------------
{
	cout << "(To play again 1=yes 0=no): ";
	cin >> repeat;

	//If the system fails it will clear it and destroy the error.
	//If it isnt a 0 or 1 it will do the same (doesnt matter) and ask for a correct input
		while (cin.fail() || (repeat != 1 && repeat != 0))
		{
			cin.clear();
			cin.ignore(1000000, '\n');

			cout << "Enter a valid number answer (1=yes 0=no): ";
			cin >> repeat;
		}
		cout << "\n";
}

//wins and losses wont need to be used in future functions, so it doesnt need &.
void WtoL(int wins, int losses)//----------------------------------------------------------------------------------------------------------------
{
	cout << "You Won " << wins;
	if (wins != 1)
	{
		cout << " Times!" << endl;
	}
	else
	{
		cout << " Time!" << endl;
	}

	cout << "You lost " << losses;
	if (losses != 1)
	{
		cout << " Times!" << endl;
	}
	else
	{
		cout << " Time!" << endl;
	}
}

//Below here is where all the random phrases get displayed ----------------------------------------------------------------------------------------

void incorrectHigh()
{
	int caseNum;

	//Gives random case between 1-10
	caseNum = rand() % 10 + 1;

	
	switch (caseNum)
	{
	case 1:
		std::cout << "Wrong Wrong Wrong Wrong! Too High!!!" << endl;
		break;
	case 2:
		std::cout << "Nope! Guess lower." << endl;
		break;
	case 3:
		std::cout << "Too high. Lower that number." << endl;
		break;
	case 4:
		std::cout << "Foolish guess. Go a bit lower." << endl;
		break;
	case 5:
		std::cout << "Bring it down." << endl;
		break;
	case 6:
		std::cout << "''Too low'' - Says the goblin" << endl;
		break;
	case 7:
		std::cout << "What are you doing. Too high. Guess again." << endl;
		break;
	case 8:
		std::cout << "It isn't that hard. Its a number from 0 to 100. You're way too high." << endl;
		
		break;
	case 9:
		std::cout << "Nope. Too big." << endl;
		break;
	case 10:
		std::cout << "Come on dude. You're over the mountains with that one!" << endl;
		break;
		
	}



}

void incorrectLow()//------------------------------------------------------------------------------------------------------------------------------
{
	int caseNum;

	caseNum = rand() % 10 + 1;


	switch (caseNum)
	{
	case 1:
		std::cout << "Too low." << endl;
		break;
	case 2:
		std::cout << "Try guessing higher." << endl;
		break;
	case 3:
		std::cout << "You can do better than this. Its bigger!" << endl;
		break;
	case 4:
		std::cout << "Bit small there bud." << endl;
		break;
	case 5:
		std::cout << "Raise that number!" << endl;
		break;
	case 6:
		std::cout << "''Too high'' -Says the goblin" << endl;
		break;
	case 7:
		std::cout << "Only way to go is up!" << endl;
		break;
	case 8:
		std::cout << "Fool. Guess higher than that." << endl;
		break;
	case 9:
		std::cout << "Bad guess. Go higher." << endl;
		break;
	case 10:
		std::cout << "Correct! Just kidding. Too Low" << endl;
		break;
	}



}

void win()//---------------------------------------------------------------------------------------------------------------------------------------
{
	int caseNum;

	caseNum = rand() % 10 + 1;


	switch (caseNum)
	{
	case 1:
		std::cout << "You actually did it!" << endl;
		break;
	case 2:
		std::cout << "Ya got it!" << endl;
		break;
	case 3:
		std::cout << "YOU ARE CORRECT!!!!" << endl;
		break;
	case 4:
		std::cout << "You got it right!" << endl;
		break;
	case 5:
		std::cout << "I guess you got it right. No celebration this time." << endl;
		break;
	case 6:
		std::cout << "You were dead on!!" << endl;
		break;
	case 7:
		std::cout << "You nailed it!" << endl;
		break;
	case 8:
		std::cout << "BOOM ya did it!" << endl;
		break;
	case 9:
		std::cout << "Spot on!" << endl;
		break;
	case 10:
		std::cout << "Good boy, you got it right!" << endl;
		break;
	}



}

void lose()//--------------------------------------------------------------------------------------------------------------------------------------
{
	int caseNum;

	caseNum = rand() % 10 + 1;


	switch (caseNum)
	{
	case 1:
		std::cout << "Pathetic!";
		break;
	case 2:
		std::cout << "Unfortunate.";
		break;
	case 3:
		std::cout << "Ugh.";
		break;
	case 4:
		std::cout << "Not even close." ;
		break;
	case 5:
		std::cout << "Failure.";
		break;
	case 6:
		std::cout << "Another one lost.";
		break;
	case 7:
		std::cout << "You lose.";
		break;
	case 8:
		std::cout << "HA!";
		break;
	case 9:
		std::cout << "Incompitence.";
		break;
	case 10:
		std::cout << "Awful.";
		break;
	}



}

void replayW()//-----------------------------------------------------------------------------------------------------------------------------------
{
	int caseNum;

	caseNum = rand() % 5 + 1;


	switch (caseNum)
	{
	case 1:
		std::cout << "Lets keep that winning streak going!" << endl;
		break;
	case 2:
		std::cout <<  "I doubt you can do it again." << endl;
		break;
	case 3:
		std::cout << "Are you really wanting to end on a win?" << endl;
		break;
	case 4:
		std::cout << "You wont get so lucky next time." << endl;
		break;
	case 5:
		std::cout << "Are ya worried about losing? Do another." << endl;
		break;
	}



}

void replayL()//-----------------------------------------------------------------------------------------------------------------------------------
{
	int caseNum;

	caseNum = rand() % 5 + 1;


	switch (caseNum)
	{
	case 1:
		std::cout << " I'll give ya another shot!" << endl;
		break;
	case 2:
		std::cout << " You'll get it next time!" << endl;
		break;
	case 3:
		std::cout << " Are you really wanting to end on a loss?" << endl;
		break;
	case 4:
		std::cout << " How many times are you wanting to lose?" << endl;
		break;
	case 5:
		std::cout << " Just give up." << endl;
		break;
	}
}