// Fill out your copyright notice in the Description page of Project Settings.

#include "MageMesh.h"


void UMageMesh::Rotate(float RelativeSpeed)
{

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	FRotator rotate(0, RawNewRotation, 0);
	//UE_LOG(LogTemp, Warning, TEXT("Rotate to %s, with change of %f"), *rotate.ToString(), GetWorld()->DeltaTimeSeconds);
	SetRelativeRotation(FRotator(0, RawNewRotation, 0)); //TODO smooth the rotation when going over the break for degrees

}

