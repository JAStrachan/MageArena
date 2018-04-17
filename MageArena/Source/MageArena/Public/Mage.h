// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mage.generated.h"

UCLASS()
class MAGEARENA_API AMage : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMage();

	//Passes the data through to the static mesh to say where to turn
	void AimAtMouse(FVector MouseDirection);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetStaffReference(UStaticMeshComponent* StaffToSet);

protected:
	

private:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector DirectionOfMouse; //Stores the direction if the mouse simplier access

	UStaticMeshComponent * Staff = nullptr;
	
};
