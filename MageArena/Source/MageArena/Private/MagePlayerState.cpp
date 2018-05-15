// Fill out your copyright notice in the Description page of Project Settings.

#include "MagePlayerState.h"
#include "MageGameModeFull.h"
#include "MagePlayerController.h"
//#include "MageGameModeFull.h" This was code to allow the event to happen in c++ not really working though




void AMagePlayerState::BeginPlay()
{
	
}

void AMagePlayerState::AddScore(float ScoreDelta) 
{
	Score += ScoreDelta;
	if (Score >= GetWorld()->GetAuthGameMode()->GetWinScore())
	{
		AMagePlayerController * MageController = Cast<AMagePlayerController>(GetOwner());
		OnPlayerWin.Broadcast(MageController); // Broadcasting that this player has won - pass in the player controller that has won
	}
}

void AMagePlayerState::AddDeaths(float DeathDelta)
{
	NoOfDeaths += DeathDelta;
}
