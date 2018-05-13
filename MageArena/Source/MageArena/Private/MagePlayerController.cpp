// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMath.h" //for RInterp
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
	AimTowardsMouse(DeltaTime);
}

//Gets the mouse Direction
void AMagePlayerController::AimTowardsMouse(float DeltaTime)
{
	if (!GetControlledMage()){return;}

	// Inspired by https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1370491-getting-a-character-to-face-the-cursor-in-a-top-down-game
	// TODO Pretty heavily modified after though...literally the first 3 lines are similar and then its fairly different
	FHitResult HitResult; //OUT parameters
	GetHitResultUnderCursor(ECC_Visibility, true, HitResult); //if it can deproject the mouse onto the world then
	FVector MouseLocation = HitResult.Location;
	
	FVector MageLocation = GetControlledMage()->GetActorLocation();
	FVector AimDirection = MouseLocation - MageLocation; //Gets the vector inbetween the two points
	// Rotate via yaw
	FVector MageForwardVector = GetActorForwardVector();
	FRotator MageRotator = MageForwardVector.Rotation();
	FRotator rotate(0, 0, 0); // Adding 90 degrees means at 270 degrees it messes up as it goes over 0
	MageRotator = MageRotator + rotate;
	FRotator AimAsRotator = AimDirection.Rotation(); //turns the unit vector into a Rotation, Roll set to 0
	
	SetControlRotation(FMath::RInterpConstantTo(MageRotator, AimAsRotator, DeltaTime, SpeedOfRotation));
}
