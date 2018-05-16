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
	AMageGameModeFull * GM = Cast<AMageGameModeFull>(GetWorld()->GetAuthGameMode());
	GM->OnActorDeath.AddDynamic(this, &AMageGameModeFull::UpdateScore);
}

void AMageGameModeFull::UpdateScore(AActor* DeadActor, AActor* KillerActor, AController* KillerActorController)
{
	UE_LOG(LogTemp, Warning, TEXT("Reached Respawn"));
	AMagePlayerState* MageKillerPlayerState = Cast<AMagePlayerState>(KillerActorController->PlayerState);
	MageKillerPlayerState->AddScore(1);
	AMage* Mage = Cast<AMage>(DeadActor);
	AMagePlayerState* MageDeadPlayerState = Cast<AMagePlayerState>(Mage->PlayerState);
	MageDeadPlayerState->AddDeaths(1);
	Respawn();
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
		AMagePlayerController* MageController = Cast<AMagePlayerController>(Iterator->Get());
		if (MageController->PlayerState->Score >= WinScore) // if player has won...
		{
			// Stop the game
			// Add UI Widget that tells you the score and takes you back to the start
			return true;
		}
	}
	return false; // if we get to here no player has won
}

void AMageGameModeFull::Respawn()
{
	
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; Iterator++)
	{
		AMagePlayerController* MageController = Cast<AMagePlayerController>(Iterator->Get());
		//if (MageController && MageController->GetPawn()==nullptr && GetMatchState() == "InProgress") //the "real" code
		if(MageController && MageController->GetPawn() == nullptr) // TODO change this to real code
		{
			
			// If cast was good and the Controller is controlling a pawn and the match is in progress
			RestartPlayer(MageController);
		}
		else
		{
			UE_LOG(LogTemp, Warning,TEXT("This mage does need a respawn :  %s"),* MageController->GetName());
		}
		
	}
}

void AMageGameModeFull::GameOver()
{

}