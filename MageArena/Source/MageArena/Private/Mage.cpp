// Fill out your copyright notice in the Description page of Project Settings.

#include "Mage.h"
#include "MageMesh.h"


// Sets default values
AMage::AMage()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMage::AimAtMouse(FVector MouseDirection)
{
	if (!Staff) { return; }

	FVector AimDirection = MouseDirection.GetSafeNormal(); //gets the normalised vector of the mouse
	MouseDirection = MouseDirection.GetSafeNormal();
	RotateMage(MouseDirection);

}

void AMage::RotateMage(FVector MouseDirection)
{
	// Rotate via yaw
	FRotator MageRotator = Mage->GetForwardVector().Rotation();
	auto AimAsRotator = MouseDirection.Rotation();
	auto DeltaRotator = AimAsRotator - MageRotator; // gets the difference
	
	
	Mage->Rotate(DeltaRotator.Yaw);
}


void AMage::SetStaffReference(UMageStaff * StaffToSet)
{
	if (!StaffToSet) { return; }
	Staff = StaffToSet;
}

void AMage::SetMageReference(UMageMesh * MageToSet)
{
	if (!MageToSet) { return; }
	Mage = MageToSet;
}

void AMage::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Cast Spell"));
}

