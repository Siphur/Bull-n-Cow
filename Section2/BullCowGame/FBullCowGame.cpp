#pragma once
#include "FBullCowGame.h"
#include <map>
// to make syntax Unreal friendly
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame()  {	Reset();} //defult constructor


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const	{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap <int32, int32 > WordLenghtToMaxTries{ {3,4},{4,7},{5,10},{6,15},{7,20} };
	return WordLenghtToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; //this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//if guess isnt isogram  
	{
		return EGuessStatus::Not_Isogram;
	}
	else if(!IsLowercase(Guess)) //if guess isnt all lowercase 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() !=GetHiddenWordLenght() )//if guess length is wrong 
	{
		return EGuessStatus::Wrong_Length;
	}
	else { return EGuessStatus::OK; } //otherwise return OK
}
// recieves a valid guess, increments turn, and return counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length(); // assuming same lenght as guess

	//loop through all the letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLenght; MHWChar++)
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLenght; GChar++)
		{
			//If they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				//if they are in the same place
				if (MHWChar == GChar) 
				{
					BullCowCount.Bulls++;//increment bulls 
				}
				//if they are not
				else 
				{
					BullCowCount.Cows++;//increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLenght) 
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 or 1 letter words as isogram
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;//setup our map
	for (char Letter : Word)	//means "for all letter of the word"
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {		//if letter is in the map
			return false; // we do NOT have isogram at this stage
		}
		else{
			LetterSeen[Letter] = true;			// add the letter to map
		}
	}
	return true; // for example in cases like /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))//if not a lower case letter
		{
			return false;
		}
		}
	return true;
}
