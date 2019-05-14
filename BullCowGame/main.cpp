/* This is the console executable that makes use of the BuildCow class. 
This acts as the view in a MVC pattern, and is responsible for all 
user int32eraction. For game logic see the FBullCowGame class.*/


#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;



void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
void PrintBack(FText Guess);
bool AskToPlayAgain();

FBullCowGame BCGame;


int main()
{
	PrintIntro();
	do {
		PlayGame();
		
	} while (AskToPlayAgain());


	return 0;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	//TODO change from FOR to WHILE loop once we are validating tries


	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		


		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << std::endl << std::endl;
		//TODO check for valid guesses
		
		
	}
	// TODO add game summary
	PrintGameSummary();
	return;

}


void PrintIntro()
{
	// introduce the game
	
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game" << std::endl;
	
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		

		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Please enter your guess #" << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << " : ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter only lower case letters.\n\n";
			break;
		default:
			Status = EGuessStatus::OK;
		}
		
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}


bool AskToPlayAgain()
{
	bool again = true;

	std::cout << "Would you like to play again? y/n: ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (tolower(Response[0]) == 'y');

}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations, you won!\n\n";
	}
	else
	{
		std::cout << "Better luck next time!\n\n";
	}
	return;
}





