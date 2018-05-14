// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPotion.h"
#include "Components/SphereComponent.h"

// Sets default values
AHealthPotion::AHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*
	PotionJarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Potion Jar"));
	RootComponent = PotionJarMesh;
	PotionJuiceMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Potion Juice"));
	PotionJuiceMesh->SetUpAttachment(PotionJarMesh);
	PotionCorkMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Potion Cork"));
	PotionCorkMesh->SetUpAttachment(PotionJarMesh);
	CollisionMesh = CreateDefaultSubobject<USphereComponent>(TEXT("Potion Cork"));
	CollisionMesh->SetUpAttachment(PotionJarMesh);
	*/
	
}

// Called when the game starts or when spawned
void AHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

