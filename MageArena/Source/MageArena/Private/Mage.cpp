// Fill out your copyright notice in the Description page of Project Settings.

#include "Mage.h"


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
	auto OurMageName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s is the direction of my mouse coming from %s"), *MouseDirection.ToString(), *OurMageName);

}

void AMage::SetStaffReference(UStaticMeshComponent * StaffToSet)
{
	Staff = StaffToSet;
}

