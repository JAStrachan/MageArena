// Fill out your copyright notice in the Description page of Project Settings.

#include "SHealthComponent.h"
#include "MageGameModeFull.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
	DefaultHealth = 100;
	MaxHealth = 200;
	bIsDead = false;
}


// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	// Only go if we are server
	if (GetOwnerRole() == ROLE_Authority)
	{
		AActor* MyOwner = GetOwner();
		if (MyOwner)
		{
			MyOwner->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::HandleTakeAnyDamage);

		}
		
	}
	Health = DefaultHealth;
}

void USHealthComponent::HandleTakeAnyDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	// Damage type should be simplest one
	if (Damage <= 0.0f || bIsDead) //if the actor is dead no reason to try and calculate damage
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
	if (Health <= 0.0f)
	{
		bIsDead = true;
	}
	if (bIsDead)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor has died"));
		AMageGameModeFull * GM = Cast<AMageGameModeFull>(GetWorld()->GetAuthGameMode()); //get the game mode so you can broadcast a death of an actor
		if (GM) //this happens on the server
		{
			GM->OnActorDeath.Broadcast(GetOwner(), DamageCauser, InstigatedBy);
		}
	}
	

}

void USHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USHealthComponent, Health);
}
