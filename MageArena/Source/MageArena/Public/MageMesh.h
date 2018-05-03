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
	void Rotate(float DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20;
	
};
