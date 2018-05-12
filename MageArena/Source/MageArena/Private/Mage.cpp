// Fill out your copyright notice in the Description page of Project Settings.

#include "Mage.h"
#include "MageStaffMesh.h"
#include "Spell.h"
#include "MageMesh.h"


// Sets default values
AMage::AMage()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SetReplicates(true);
	//SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AMage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMage::SetStaffReference(UMageStaffMesh * StaffToSet)
{
	if (!StaffToSet) { return; }
	Staff = StaffToSet;
}

void AMage::SetMageReference(UMageMesh * MageToSet)
{
	if (!MageToSet) { return; }
	Mage = MageToSet;
}

// Input setup is in Blueprint
void AMage::MoveForward(float force)
{
	// TODO Remove UE_LOG(LogTemp, Warning, TEXT("Moving forward with force : %f"), force);
	if (force != 0.0f)
	{
		// Add movement in that directions
		//TODO Will be off by 90 degrees as the x-plane is in wrong direction
		AddMovementInput(Mage->GetForwardVector(), force);
	}
}

void AMage::MoveRight(float force)
{
	// TODO Remove UE_LOG(LogTemp, Warning, TEXT("Moving right with force : %f"), force);
	if (force != 0.0f)
	{
		// Add movement in that direction
		//TODO Will be off by 90 degrees as the x-plane is in wrong direction
		AddMovementInput(Mage->GetRightVector(), force);
	}

}

// Called from MagePlayerController which finds the mouse location in the world
// This then gets the player's location and finds the normalised vector between them
void AMage::AimAtMouse(FVector MouseLocation)
{
	ServerAimToMouse(MouseLocation);
	/*if (!Staff) { return; }
	FVector MageLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector AimDirection = MouseLocation - MageLocation; // The right way round
	AimDirection = AimDirection.GetSafeNormal(); // gets the normalised vector of the mouse
	RotateMage(AimDirection); // gives the direction to aim at to Rotate mage*/

}

void AMage::RotateMage(FVector AimDirection) //wont need this if we just use the server implementation
{
	/*// Rotate via yaw
	FRotator MageRotator = Mage->GetForwardVector().Rotation();
	//FRotator rotate(0, 90, 0); // TODO Adding 90 degrees means at 270 degrees it messes up as it goes over 0
	//MageRotator = MageRotator + rotate; // makes it so the head points to the mouse
	FRotator AimAsRotator = AimDirection.Rotation(); //turns the unit vector into a Rotation, Roll set to 0
	FRotator DeltaRotator = AimAsRotator - MageRotator; //gets the difference
	
	
	//TODO This works. Start a refactor so we can have this code possibly in this class or component
	auto RelativeSpeed = DeltaRotator.Yaw;
	Mage->AddRelativeRotation(FRotator(0, RelativeSpeed, 0)); //SMOOOTHED THE HECK OUT OF IT
	*/
}
//Thought it might be a solution but doesn't seem to be
void AMage::ServerAimToMouse_Implementation(FVector MouseLocation)
{
	if (!Staff) { return; }
	FVector MageLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	if (Role < ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("Client is trying to rotate using server method"), *MageLocation.ToString());
	}
	FVector AimDirection = MouseLocation - MageLocation; // The right way round
	AimDirection = AimDirection.GetSafeNormal(); // gets the normalised vector of the mouse
	ServerRotateMage(AimDirection); // gives the direction to aim at to Rotate mage
}

bool AMage::ServerAimToMouse_Validate(FVector MouseLocation)
{
return true;
} //TODO fill with actual checking code

void AMage::ServerRotateMage_Implementation(FVector AimDirection)
{
	// Rotate via yaw
	FRotator MageRotator = Mage->GetForwardVector().Rotation();
	//FRotator rotate(0, 90, 0); // TODO Adding 90 degrees means at 270 degrees it messes up as it goes over 0
	//MageRotator = MageRotator + rotate; // makes it so the head points to the mouse
	FRotator AimAsRotator = AimDirection.Rotation(); //turns the unit vector into a Rotation, Roll set to 0
	FRotator DeltaRotator = AimAsRotator - MageRotator; //gets the difference


	// TODO This works. Start a refactor so we can have this code possibly in this class or component
	auto RelativeSpeed = DeltaRotator.Yaw;
	
	Mage->AddRelativeRotation(FRotator(0, RelativeSpeed, 0)); //SMOOOTHED THE HECK OUT OF IT
}

bool AMage::ServerRotateMage_Validate(FVector AimDirection)
{
return true;
} // TODO fill with actual checking code




void AMage::Fire()
{
	ServerFire();
	// add any code that clients want to do when they fire
}

// Calling ServerFire() calls to the server and asks to run the serverfire_implementation method
void AMage::ServerFire_Implementation() // implementation of server fire. Call ServerFire() to actually call it
{
	//GetTimeSeconds are used so that time is consistent across states, not just on each platform.

	if (!SpellBlueprint)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpellBlueprint isn't set, Reset it in the Mage_BP")); //warning in case it removes the spell blueprint from the Mage_BP
		return;
	}
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds; // true if the time passed in game is greater than the reload time. 
	if (Staff && isReloaded)
	{
		// Spawns a spell projectile
		auto Spell = GetWorld()->SpawnActor<ASpell>(
			SpellBlueprint,
			Staff->GetSocketLocation(FName("Spell")),
			Staff->GetSocketRotation(FName("Spell"))
			);

		Spell->LaunchSpell(LaunchSpeed);
		float LastFireTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		return;
	}
}

bool AMage::ServerFire_Validate() //have to have this when you have WithValidation
{
	return true; //checks to see if the player is cheating or not
}

