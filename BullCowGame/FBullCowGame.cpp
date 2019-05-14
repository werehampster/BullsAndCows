#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;



FBullCowGame::FBullCowGame()
{
	Reset();
}

// Getters
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if guess isn't isorgam return error
	if (!IsIsogram(Guess)) //TODO write function
	{
		return EGuessStatus::Not_Isogram;
	}
	// if the guess isn't lowercase return error
	else if (!IsLowercase(Guess)) //TODO Write function
	{
		return EGuessStatus::Not_Lowercase;
	}
	
	// if guess length is wrong return error
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
		
	}
	// otherwise return OK
	else
	{
		return EGuessStatus::OK;
	}
}

//receives a valid guess, increments turn and returns count

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{	
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	

	// loop through all letter in the hidden word
	for (int32 i = 0; i < GetHiddenWordLength(); i++)
	{
		if (MyHiddenWord[i] == Guess[i])
		{
			BullCowCount.Bulls++;
			

		}
		//compare letters against the guess
		for (int32 j = 0; j < GetHiddenWordLength(); j++)
		{
			if (MyHiddenWord[i] == Guess[j] && j != i)
			{
				BullCowCount.Cows++;
			}
		}	
	}
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	
	

	return;
}

bool FBullCowGame::IsIsogram(FString Guess) const 
{	
	// treat 0 and 1 letter words as isograms
	if (Guess.length() <= 1) { return true; }

	//create TMap

	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess) //for all letters of the Guess
	{
		Letter = tolower(Letter); // to handle mixed case
		
		// if the letter already exists in the map the word is not an isogram
		if(LetterSeen[Letter])
			return false;
		else
		{
			// if the letter doesn't exist in the map yet, add it
			LetterSeen[Letter] = true;
		}
	}
	return true; 
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{	 
		if (!islower(Letter) && Letter != ' ' && Letter != '\0')
		{
			return false;
		}
	}
	return true;
}
