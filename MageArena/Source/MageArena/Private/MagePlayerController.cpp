// Fill out your copyright notice in the Description page of Project Settings.

#include "MagePlayerController.h"

AMage * AMagePlayerController::GetControlledMage() const
{
	return Cast<AMage>(GetCharacter());
}

void AMagePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMagePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsMouse();
}

//Gets the mouse Direction
void AMagePlayerController::AimTowardsMouse()
{
	if (!GetControlledMage()){return;}

	// Inspired by https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1370491-getting-a-character-to-face-the-cursor-in-a-top-down-game
	FHitResult hitResult; //OUT parameters
	GetHitResultUnderCursor(ECC_Visibility, true, hitResult); //if it can deproject the mouse onto the world then
	FVector HitLocation = hitResult.Location;
	GetControlledMage()->AimAtMouse(HitLocation); //passes the location down
	
}


