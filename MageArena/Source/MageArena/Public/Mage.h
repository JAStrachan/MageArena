// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mage.generated.h"

//forward declaration
class UMageMesh;
class UMageStaffMesh;
class ASpell;
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

	UFUNCTION(BlueprintCallable)
	void MoveForward();

	UFUNCTION(BlueprintCallable)
	void MoveRight();

protected:
	

private:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100; //Vaguely sensible on how fast it goes

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 1.5;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<ASpell> SpellBlueprint;

	FVector DirectionOfMouse; //Stores the direction 0f the mouse for simplier access

	float LastFireTime = 0; // The last time the mage fired a spell in seconds

	UMageMesh * Mage = nullptr;

	UMageStaffMesh * Staff = nullptr;
	
};
