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

	//Get mouse location if it can be found
	//get vector between player and mouse
	//Push down to rotate component

	FVector MouseLocation, MouseDirection; //OUT parameters
	if (DeprojectMousePositionToWorld(MouseLocation, MouseDirection)) //if it can deproject the mouse onto the world then
	{
		GetControlledMage()->AimAtMouse(MouseDirection); //passes the rotation down
	}
}
