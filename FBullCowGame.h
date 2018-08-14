#pragma once   
#include <string>

using fString = std::string;
using int32 = int;


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;

};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame 
{
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;	  
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const; 
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(fString) const; 

	void Reset();
	FBullCowCount SubmitGuess(fString);

 
private:
	
	int32 MyCurrentTry;
	fString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsIsogram(fString) const;
	bool IsLowerCase(fString) const;
};
