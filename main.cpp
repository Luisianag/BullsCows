/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction.
for game logic to see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using fText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
fText GetValidGuess();
bool AskToPlayAgain();


FBullCowGame BCGame; //instantiate a new game

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		
		bPlayAgain = AskToPlayAgain();

		std::cout << std::endl;
		
	} 
	while (bPlayAgain);

	return 0;
}

//	introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows\n";
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Enter Level: " << std::endl;
	std::cout << " 1. Beginner (5 Letter word) \n 2. Normal (7 Letter word) \n 3. Advanced (10 Letter word)" << std::endl;
	std::cout << "Can you guess " << BCGame.GetHiddenWordLength(); // TODO give user the option to change length of word
	std::cout << " the letter isogram I'm thinking of?\n";
	       
	return;
}
//	get a guess from the player
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	   
	
	 //TODO change FOR to While loop once we are validating tries
	 //WHILE the game is NOT won
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		fText Guess = GetValidGuess();

		//submit valid guess to the game & receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n\n";
		
	}

	// TODO summarize game
	PrintGameSummary();
	return;
}


fText GetValidGuess()
{
	fText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 MyCurrentTry = BCGame.GetCurrentTry();
		std::cout << std::endl;
		std::cout << "Try " << MyCurrentTry << " of  " << BCGame.GetMaxTries();
		std::cout << std::endl;
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until no errors are found
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word (y/n)?" << std::endl;
	fText Response = ""; 
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');

}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << " WELL DONE - YOU WIN!!! " << std::endl;
	}
	else
	{
		std::cout << " :( BETTER LUCK NEXT TIME! " << std::endl;

	}
}