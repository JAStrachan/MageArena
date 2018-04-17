// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mage.h"
#include "GameFramework/PlayerController.h"
#include "MagePlayerController.generated.h"

/**
 * Written By James Strachan
	Class that handles input for the mage character
 */
UCLASS()
class MAGEARENA_API AMagePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AMage* GetControlledMage() const;
	
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//Collects the mouse direction and passes it to the Mage class
	void AimTowardsMouse();
};
