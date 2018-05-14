// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPotion.generated.h"

class USphereComponent;

UCLASS()
class MAGEARENA_API AHealthPotion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPotion();

protected:
	UStaticMeshComponent * PotionJarMesh = nullptr;

	UStaticMesh * PotionJuiceMesh = nullptr;

	UStaticMesh * PotionCorkMesh = nullptr;

	USphereComponent * CollisionMesh = nullptr;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
