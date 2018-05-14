// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mage.generated.h"

//forward declaration
class UMageMesh;
class UMageStaffMesh;
class ASpell;
class USHealthComponent;

//Mage class, holds mage properties and basic movement methods
UCLASS()
class MAGEARENA_API AMage : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMage();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetStaffReference(UMageStaffMesh* StaffToSet);

	//UFUNCTION(BlueprintCallable, Category = Setup)
	//void SetSpringArmReference(SpringArm)

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void MoveForward(float force);

	UFUNCTION(BlueprintCallable)
	void MoveRight(float force);

protected:
	UFUNCTION(Server, Reliable, WithValidation) // Server denotes its a server function, Reliable denotes that all data will eventually get to the server. 
	void ServerFire(); // With validation is always needed for server functions

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	USHealthComponent* HealthComp;

	UFUNCTION()
	void OnHealthChanged(USHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Death")
	bool bDied;
private:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 1500; //Vaguely sensible on how fast it goes

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 1.5;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<ASpell> SpellBlueprint;

	float LastFireTime = 0; // The last time the mage fired a spell in seconds

	UMageStaffMesh * Staff = nullptr;

	FVector CameraRotation = FVector(0, 0, 0);

};
