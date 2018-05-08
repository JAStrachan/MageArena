// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mage.generated.h"

//forward declaration
class UMageMesh;
class UMageStaffMesh;
//Mage class, holds mage properties and basic movement methods
UCLASS()
class MAGEARENA_API AMage : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMage();

	//Passes the data through to the static mesh to say where to turn
	void AimAtMouse(FVector MouseDirection);

	void RotateMage(FVector MouseDirection);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetStaffReference(UMageStaffMesh* StaffToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetMageReference(UMageMesh * MageToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	

private:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector DirectionOfMouse; //Stores the direction 0f the mouse for simplier access

	UMageStaffMesh * Staff = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100; //Vaguely sensible on how fast it goes

	UMageMesh * Mage = nullptr;
	
};
