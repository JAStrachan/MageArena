// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "MageMesh.generated.h"

/**
 * 
 */
UCLASS( meta = (BluePrintSpawnableComponent))
class MAGEARENA_API UMageMesh : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
	
public:
	// TODO check this is right
	// -1 is max left movement and +1 is max right movement
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20;
	
};
