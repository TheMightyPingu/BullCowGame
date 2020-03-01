
#include "BullCowCartridge.h" 
#include "HiddenWordList.h"

// When the game starts
void UBullCowCartridge::BeginPlay() 
{
    Super::BeginPlay();

    //Get Valid Words
    Isograms = GetValidWords(HiddenWords);

    // Start Game
    SetupGame();
    
    //Debug Lines
    // PrintLine(TEXT("The Number Of Possible Words Are: %i"), HiddenWords.Num()); 
    // PrintLine(TEXT("The Number Of Valid Words Are: %i"), Isograms.Num());
    // PrintLine(TEXT("The Hidden Word Is: %s."), *HiddenWord);
}


// When the player hits enter
void UBullCowCartridge::OnInput(const FString& PlayerInput) 
{
        
    // Clear Screen and Start New Game If Game is Over
    if (bGameOver)
    {   
        ClearScreen();
        SetupGame();
    }

    // If Not Over, Process Player's Guess
    else 
    {
        ProcessGuess(PlayerInput);
    }

}

// Initialize Game
void UBullCowCartridge::SetupGame() {

    // Game Start
    bGameOver = false;

    // Welcome Player
    PrintLine(TEXT("Welcome to The Bulls and Cows Game!"));
   
    // Set Hidden Word
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)] ;

    // Get Hidden Word Count
    HiddenWordCount = HiddenWord.Len();

    // Set Lives To Equal Length of HiddenWord
    Lives = HiddenWordCount * 2;  

    // Show Hidden Word Characters
    PrintLine(TEXT("Guess The Hidden Word of %i Characters."), HiddenWordCount);

    // Show Lives Count
    PrintLine(TEXT("You Have %i Lives."), Lives);

    // Prompt To Type Guess
    PrintLine(TEXT("Press Tab to Type In Your Guess:"));

}

// End Game IF Player Has Lost or Won
void UBullCowCartridge::EndGame() {

    bGameOver = true;
    PrintLine(TEXT("The Hidden Word Was: %s."), *HiddenWord);
    PrintLine(TEXT("\nHit Enter To Play Again or \"Esc\" to Exit."));

}

void UBullCowCartridge::ProcessGuess(const FString& Guess) {

        //Input Word Count
        int32 GuessWordCount = Guess.Len();

        // Check If Input Is Identical to Hidden Word
        if(Guess == HiddenWord) 
        {
            ClearScreen();
            PrintLine(TEXT("Correct! You Win."));
            EndGame();
            return;
        }

        
        // Check if Length of Guess Characters are Equal To Hidden Word
        if (GuessWordCount != HiddenWordCount)
        {
            PrintLine(TEXT("The Word Is %i Letters Long."), HiddenWordCount); 
            PrintLine(TEXT("Try Again or Hit \"Esc\" to Exit."));
            return;
        }  

        // Check If Guess Has Repeating Letters
        if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("The Word Has No Repeating Letters."));
            PrintLine(TEXT("Try Again or Hit \"Esc\" to Exit."));
            return;
        }
 
        --Lives;
        PrintLine(TEXT("Guess Again. You Have %i Lives Left."), Lives);

        if (Lives <= 0)
        {
            ClearScreen();
            PrintLine(TEXT("You Have No Lives Left. You Lose!"));
            EndGame();
        }

        // Show Bulls and Cows Score For Player's Guess
        FBullCowCount PlayerScore = GetBullCows(Guess);
        PrintLine(TEXT("You Have %i Bulls and %i Cows."), PlayerScore.Bulls, PlayerScore.Cows);
}

// Check If Guess Is Isogram
bool UBullCowCartridge::IsIsogram(const FString& Word) const {
    
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }  
        }
    }
    
  return true;  
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const {

    TArray<FString> ValidWords;

    // Check If Word Is Valid Isograms And Store It
    for (FString CurrentWord : WordList)
    {
        if(CurrentWord.Len() >= 4 && IsIsogram(CurrentWord)) {

            ValidWords.Emplace(CurrentWord);

        }
    }
    
    return ValidWords;  
}

// Get BullCowCount
FBullCowCount UBullCowCartridge::GetBullCows(const FString& PlayerGuess) const {

    FBullCowCount Count;
 
    for (int32 GuessIndex = 0; GuessIndex < PlayerGuess.Len(); GuessIndex++)
    {
        // If matching letters in their right positions, add bulls
        if (PlayerGuess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            // If matching letters in different positions, add cows
            if (PlayerGuess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    } 
    return Count;
}