// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MagePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MAGEARENA_API AMagePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Scoring")
	void AddScore(float ScoreDelta); 
	// Normal Playerstate has a normal add score method but its only BlueprintReadable, this method means we can call it in blueprint
	
};
