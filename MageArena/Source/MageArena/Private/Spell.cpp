// Fill out your copyright notice in the Description page of Project Settings.

#include "Spell.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"



// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);
	CollisionMesh->OnComponentHit.AddDynamic(this, &ASpell::OnHit);

	SpellBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Spell Blast"));
	SpellBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpellMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Spell Movement"));
	SpellMovement->bAutoActivate = false; // it go flying off until we fire it.

	SetReplicates(true); // restart editor if not working, sometimes unreal bugs
	SetReplicateMovement(true); // these say to clients please spawn all the projectiles the server creates
	
}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpell::LaunchSpell(float Speed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	
	SpellMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed); // TODO x plane in wrong direction, add vector on it if need to move spell in right direction
	SpellMovement->Activate(); // activate the movement - we turned this off in the constructor
}

void ASpell::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Generated hit event"));
	Destroy();

}
