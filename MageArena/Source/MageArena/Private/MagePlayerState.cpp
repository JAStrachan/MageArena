// Fill out your copyright notice in the Description page of Project Settings.

#include "MagePlayerState.h"
#include "Net/UnrealNetwork.h"
#include "MageGameModeFull.h"
#include "MagePlayerController.h"

void AMagePlayerState::BeginPlay()
{

}

void AMagePlayerState::AddScore(float ScoreDelta) 
{
	Score += ScoreDelta;
	/*if (Score >= Cast<AMageGameModeFull>(GetWorld()->GetAuthGameMode())->GetWinScore()) // Gets the custom game mode and then checks whats the number of points needed to win
	{
		if (!Cast<AMagePlayerController>(GetOwner())) { return; }
		AMagePlayerController * MageController = Cast<AMagePlayerController>(GetOwner());
		//OnPlayerWin.Broadcast(MageController); // Broadcasting that this player has won - pass in the player controller that has won
	}*/
}

void AMagePlayerState::AddDeaths(float DeathDelta)
{
	NoOfDeaths += DeathDelta;
}
