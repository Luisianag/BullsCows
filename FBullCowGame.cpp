#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map		   //to make syntax Unreal friendly

using int32 = int;

FBullCowGame::FBullCowGame()  {  Reset(); }	 //constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry;	}
int32 FBullCowGame::GetHiddenWordLength()	const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries()	const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,13}, {7,15} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	const fString HiddenWord = "plane";
	MyHiddenWord = HiddenWord;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

FBullCowCount FBullCowGame::SubmitGuess(fString Guess)
{
	//increment the turn number
	MyCurrentTry++;
	
	//setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letter in the guess

	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) 
	{	
		//compare letter against the hidden word 1 @ a time
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) 
		{
			//if they match
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				//if they're in the same plae
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;	 //increment bulls
				}
				else {
					BullCowCount.Cows++; //must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(fString Word) const
{
	//treat 0 and 1 letter words as Isograms
	if (Word.length() <= 1) { return true; }
	
	TMap<char, bool> LetterSeen;//set up map
	for (auto Letter : Word) //for all letters of the word 
	{
		Letter = tolower(Letter); //handle mixed case
		
		if (LetterSeen[Letter]) 	 //if the letter is in the map
		{ 
			return false;		      //we do NOT have an Isogram
		} 
		else 
		{ 
			LetterSeen[Letter] = true; 
		}
	}
	
	return true;
}

bool FBullCowGame::IsLowerCase(fString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }		//if not lowercase //return false			
		else { return true;  }
	}
	return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(fString Guess) const
{
	if (!IsIsogram(Guess))		//If the guess isn't an isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))	//If  the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())	//If the length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}
