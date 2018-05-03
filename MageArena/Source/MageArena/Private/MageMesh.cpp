// Fill out your copyright notice in the Description page of Project Settings.

#include "MageMesh.h"


void UMageMesh::Rotate(float DegreesPerSecond)
{
	UE_LOG(LogTemp, Warning, TEXT("Mage Rotate called at speed %f"), DegreesPerSecond);
	// Work out current difference between current mage rotation and mousedirection
	// Move the mage the right amount this frame
}

