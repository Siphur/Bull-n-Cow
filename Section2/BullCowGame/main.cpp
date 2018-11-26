/*This is the console executable makes use of BullCow class
This acts as the view in a MVC pattern, and is responisble for all 
users interaction.For game logic see the FBullCowGame.

*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using int32 = int32;
using FText = std::string;

//function prototypes as outside a class
void PrintIntro();
FText Difficulty();
void PlayGame();
FText GetValidGuess();
bool AsktoPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// entry point for application
int main()
{

	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AsktoPlayAgain();
	} 
	while (bPlayAgain);
	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the 6 letter";
	std::cout << "isogram i am thinking of?\n";
	std::cout << std::endl;
	return ;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loops asking for guesses while game is not won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)	{ 
		FText Guess = GetValidGuess(); 

		// Submit Valid guess to game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop until user gives valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do 
	{
		// get a guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " out of " << BCGame.GetMaxTries();
		std::cout << ". Enter your Guess:";
		std::getline(std::cin, Guess);
		std::cout << std::endl;

		//check status give back report
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Your Guess isn't an isogram\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "All guess letters must be lower case\n";
			break;
		default:
			// assume guess is valid
			break;
		}
		std::cout << std::endl ;
	} while (Status != EGuessStatus::OK); //keep looping until get no errors
	return Guess;
}

bool AsktoPlayAgain()
{ 
	std::cout << "Do you want to play again with same hidden word?(y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done\nYou Win\n\n";
	}
	else
	{
		std::cout << "Ooops You Lost\nBetter Luck Next Time\n\n";
	}
}
