#include "FGEnemyHealthComponent.h"

UFGEnemyHealthComponent::UFGEnemyHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFGEnemyHealthComponent::Stunned()
{
	UE_LOG(LogTemp, Warning, TEXT("EnemyHit"));
}

