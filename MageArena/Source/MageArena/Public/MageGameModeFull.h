// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MageGameModeFull.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorDeath, AActor*, DeadActor, AActor*, KillerActor, AController*, KillerActorController);
// Technically at this stage we only the last parameter but forward planning is nice
// Deadactor is so we can tell what died - if we implement a system where people lose score or we count their deaths this would be important
// KillerActor is the actor that killed the DeadActor - this could be spell of some sort. Handy to have for output messages and other gameplay stats
// KillerActorController is the actor thats is responsible for causing the death ie the mage that sent the spell. We need this to give players scores when they kill

/**
 * The Gamemode of the Mage Arena Game.
   Determines winners and when to actually start and end the game
 */
UCLASS()
class MAGEARENA_API AMageGameModeFull : public AGameMode
{
	GENERATED_BODY()
	
public:
	bool CheckIfPlayerHasWon(); // Checks if a player has achieved the score needed to win the game
	
	AMageGameModeFull();

	void GameOver(); // Game over when one player wins

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
	FOnActorDeath OnActorDeath;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Win Condition")
	int32 WinScore = 10;

};
