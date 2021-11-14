#pragma once

#include "Components/ActorComponent.h"
#include "FGEnemyHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UFGEnemyHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFGEnemyHealthComponent();

	void Stunned();
};