#include "FGHealthComponent.h"

#include "GP4_Team10/FGGameInstance.h"
#include "GP4_Team10/GP4_Team10GameModeBase.h"
#include "GP4_Team10/FGSaveSystem/FGMainSaveGame.h"
#include "Kismet/GameplayStatics.h"

UFGHealthComponent::UFGHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UFGHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = Health;
}

void UFGHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Timer += DeltaTime;
	RevivePlayer();
}

void UFGHealthComponent::TakeDamage(int DamageTaken)
{
	if(Timer > InvulnerableDuration)
	{
		CurrentHealth -= DamageTaken;
		if(CurrentHealth < 0)
		{
			CurrentHealth = 0;
			OnPlayerDeath.Broadcast(GetOwner()->GetActorLocation());
		}
		else
			OnTakeDamage.Broadcast(GetOwner()->GetActorLocation());
		Timer = 0;
	}
}

void UFGHealthComponent::RevivePlayer()
{
	if(CurrentHealth <= 0)
	{
		auto* GameMode = Cast<AGP4_Team10GameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode == nullptr) {return;}

		GameMode->RespawnPlayer();
		CurrentHealth = Health;
	}
}

void UFGHealthComponent::PlayerRevived()
{
	OnPlayerRevived.Broadcast(GetOwner()->GetActorLocation());
}



