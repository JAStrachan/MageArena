// Fill out your copyright notice in the Description page of Project Settings.

#include "Mage.h"
#include "MageStaffMesh.h"
#include "Spell.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "ObjectPool.h"
#include "SHealthComponent.h"
#include "MageMesh.h"


// Sets default values
AMage::AMage()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	SetReplicateMovement(true);
	bUseControllerRotationYaw = true;
	bDied = false;

	HealthComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));
}



// Called when the game starts or when spawned
void AMage::BeginPlay()
{
	Super::BeginPlay();
	

	HealthComp->OnHealthChanged.AddDynamic(this, &AMage::OnHealthChanged);
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

void AMage::SetStaffReference(UMageStaffMesh * StaffToSet)
{
	if (!StaffToSet) { return; }
	Staff = StaffToSet;
}


// Input setup is in Blueprint
void AMage::MoveForward(float force)
{
	
	if (force != 0.0f)
	{
		// Add movement in that directions
		AddMovementInput(FVector(1, 0, 0), force); // The vector just depicts forward in world space, rather than relative to where the actor is facing
	}
}

void AMage::MoveRight(float force)
{
	
	if (force != 0.0f)
	{
		//Add movement in that direction
		AddMovementInput(FVector(0,1,0), force);
	}

}

void AMage::Fire()
{
	ServerFire();
	// add any code that clients want to do when they fire
}

// Calling ServerFire() calls to the server and asks to run the serverfire_implementation method
void AMage::ServerFire_Implementation() // implementation of server fire. Call ServerFire() to actually call it
{
	//GetTimeSeconds are used so that time is consistent across states, not just on each platform.

	if (!SpellBlueprint)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpellBlueprint isn't set, Reset it in the Mage_BP and reset it to the Spell_BP_Retry")); //warning in case it removes the spell blueprint from the Mage_BP
		return;
	}
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds; // true if the time passed in game is greater than the reload time. 
	if (Staff && isReloaded)
	{
		FActorSpawnParameters parameters;
		parameters.Instigator = Controller->GetPawn(); //Gets the pawn responsible for the damage - 
		//this would be in the mage. In spell.cpp we specify the mage's player controller when applying damage
		
		// Spawns a spell projectile
		auto Spell = GetWorld()->SpawnActor<ASpell>(
			SpellBlueprint,
			Staff->GetSocketLocation(FName("Spell")),
			Staff->GetSocketRotation(FName("Spell"))+FRotator(0,90,0),
			parameters
			); //the last FRotator is a fix as the spell's x plane seems to be 90 degrees off where I want it
			// parameters is the list of parameters just used so I can get the instigator of the damagea
		Spell->LaunchSpell(LaunchSpeed);
		float LastFireTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		return;
	}
}

bool AMage::ServerFire_Validate() //have to have this when you have WithValidation
{
	return true; //checks to see if the player is cheating or not
}

void AMage::OnHealthChanged(USHealthComponent * OwningHealthComp, float Health, float HealthDelta, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Health <= 0.0f && !bDied)
	{
		// Die!

		GetMovementComponent()->StopMovementImmediately();

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		bDied = true;

		DetachFromControllerPendingDestroy();

		SetLifeSpan(0.5f); //TODO set up a death animation of it just disappearing
	}
}

void AMage::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMage, bDied);
}
