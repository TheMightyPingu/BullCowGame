// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

// When the game starts
void UBullCowCartridge::BeginPlay() 
{
    Super::BeginPlay();

    SetupGame();

}


// When the player hits enter
void UBullCowCartridge::OnInput(const FString& Input) 
{
    
    //Input Word Count
    int32 InputWordCount = Input.Len();
    
    // Clear Screen and Start New Game If Game is Over
    if (bGameOver)
    {   
        ClearScreen();
        SetupGame();
    }
    
    // If Not Over, Check If Won or Lost
    else 
    {
        // Check If Input Is Identical to Hidden Word
        if(Input == HiddenWord) 
        {
            PrintLine(TEXT("Correct! You Win."));
            EndGame();
        }
 
        else 
        {

            if (InputWordCount != HiddenWordCount)
                {
                    PrintLine(TEXT("The Word Is %i Characters Long. Try Again."), HiddenWordCount); 
                }  
            
        }   

    }




    // Check If Isogram
    // Check If Right Number of Characters

    // Check If Lives > 0
        // If Yes, Congrajulate Player and Prompt For New Game
        // If No, Show Fail Message, Decrement Life and Prompt For New Guess
    // Exit Game

    

}

// Initialize Game
void UBullCowCartridge::SetupGame() {

    // Game Start
    bGameOver = false;

    // Welcome Player
    PrintLine(TEXT("Welcome To the Bulls and Cows Game!"));
   
    // Set Hidden Word
    HiddenWord = TEXT("Neurotic");

    // Get Hidden Word Count
    HiddenWordCount = HiddenWord.Len();

    // Set Lives
    Lives = 5;  

    // Show Hidden Word Characters
    PrintLine(TEXT("Guess The Hidden Word of %i Characters"), HiddenWordCount);

    // Show Lives Count
    PrintLine(TEXT("You Have %i Lives"), Lives);

    // Prompt To Type Guess
    PrintLine(TEXT("Type In Your Guess:"));

}

void UBullCowCartridge::EndGame() {

    bGameOver = true;
    PrintLine(TEXT("Press Enter To Play Again"));

}