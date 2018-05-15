// Fill out your copyright notice in the Description page of Project Settings.

#include "MageGameModeFull.h"
#include "SHealthComponent.h"
#include "MageGameState.h"
#include "MagePlayerState.h"

AMageGameModeFull::AMageGameModeFull()
{
	GameStateClass = AMageGameState::StaticClass();
	PlayerStateClass = AMagePlayerState::StaticClass(); // Explicitly telling us that those are what we are using
}

void AMageGameModeFull::GameOver()
{
}

bool AMageGameModeFull::CheckIfPlayerHasWon()
{
	return false; // TODO add checking code
}