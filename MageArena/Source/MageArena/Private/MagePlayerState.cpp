// Fill out your copyright notice in the Description page of Project Settings.

#include "MagePlayerState.h"
#include "Net/UnrealNetwork.h"
#include "MageGameModeFull.h"
#include "MagePlayerController.h"


AMagePlayerState::AMagePlayerState()
{
}



void AMagePlayerState::BeginPlay()
{

}

void AMagePlayerState::AddScore(float ScoreDelta) 
{
	Score += ScoreDelta;
	UE_LOG(LogTemp, Warning, TEXT("Score of player : %f"), Score);
}

void AMagePlayerState::AddDeaths(float DeathDelta)
{
	NoOfDeaths += DeathDelta;
}
