// Fill out your copyright notice in the Description page of Project Settings.

#include "Spell.h"


// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpellMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Spell Movement"));
	SpellMovement->bAutoActivate = false; // it go flying off until we fire it.

	SetReplicates(true);
	SetReplicateMovement(true); // these say to clients please spawn all the projectiles the server creates

}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpell::LaunchSpell(float Speed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f:  Staff Shoots with speed %f"), Time, Speed);
	SpellMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed); // TODO x plane in wrong direction, add vector on it if need to move spell in right direction
	SpellMovement->Activate(); // activate the movement - we turned this off in the constructor
}

