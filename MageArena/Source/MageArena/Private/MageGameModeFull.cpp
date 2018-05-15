// Fill out your copyright notice in the Description page of Project Settings.

#include "MageGameModeFull.h"
#include "SHealthComponent.h"
#include "MageGameState.h"
#include "MagePlayerController.h"
#include "MagePlayerState.h"

AMageGameModeFull::AMageGameModeFull()
{
	GameStateClass = AMageGameState::StaticClass();
	PlayerStateClass = AMagePlayerState::StaticClass(); // Explicitly telling us that those are what we are using
}

void AMageGameModeFull::GameOver()
{
}

void AMageGameModeFull::BeginMatch()
{
}

int32 AMageGameModeFull::GetWinScore()
{
	return WinScore;
}

bool AMageGameModeFull::CheckIfPlayerHasWon()
{ 
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; Iterator++)
	{
		AMagePlayerController* MageController;
		if (MageController->PlayerState->Score >= WinScore) // if player has won...
		{
			// Stop the game
			// Add UI Widget that tells you the score and takes you back to the start
		}
	}
}