/*The game logic (no view code or user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

//to make syntax Unreal friendly
using int32 = int;
using FString = std::string;

//two integer initiliazed to zero
struct FBullCowCount 
{
	int32 Bulls = 0 ;
	int32 Cows = 0 ;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const ;  

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialization
	FString MyDifficulty;
	int32 MyCurrentTry;
	FString  MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};