// This code was heavily inspired by https://www.youtube.com/watch?v=g4pAO01FFlQ

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPool.generated.h"

// A component that holds the object pool for spells
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAGEARENA_API UObjectPool : public UActorComponent
{
	GENERATED_BODY()
};
