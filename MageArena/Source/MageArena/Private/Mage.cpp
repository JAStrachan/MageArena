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

//Called from MagePlayerController which finds the mouse location in the world
// This then gets the player's location and finds the normalised vector between them
void AMage::AimAtMouse(FVector MouseLocation)
{
	if (!Staff) { return; }
	FVector MageLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Actor Location %s"), *MageLocation.ToString());
	FVector AimDirection = MouseLocation - MageLocation; // The right way round
	AimDirection = AimDirection.GetSafeNormal(); // gets the normalised vector of the mouse
	RotateMage(AimDirection); // gives the direction to aim at to Rotate mage

}

void AMage::RotateMage(FVector AimDirection)
{
	// Rotate via yaw
	FRotator MageRotator = Mage->GetForwardVector().Rotation();
	FRotator rotate(0, 90, 0); 
	MageRotator = MageRotator + rotate; // makes it so the head points to the mouse
	FRotator AimAsRotator = AimDirection.Rotation(); //turns the unit vector into a Rotation, Roll set to 0
	FRotator DeltaRotator = AimAsRotator - MageRotator; //gets the difference
	
	
	Mage->Rotate(DeltaRotator.Yaw);
}


void AMage::SetStaffReference(UMageStaffMesh * StaffToSet)
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

