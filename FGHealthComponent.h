#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamage, FVector, EventSourceLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDeath, FVector, EventSourceLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerRevived, FVector, EventSourceLocation);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UFGHealthComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGHealthComponent();
	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RevivePlayer();
	void PlayerRevived();
	UFUNCTION(BlueprintCallable)
		void TakeDamage(int DamageTaken);

	UPROPERTY(BlueprintAssignable)
	FOnTakeDamage OnTakeDamage;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerDeath OnPlayerDeath;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerRevived OnPlayerRevived;

private:
	float Timer;
	int CurrentHealth;
	UPROPERTY(EditAnywhere)
		int Health;
	UPROPERTY(EditDefaultsOnly)
		float InvulnerableDuration;
};