#pragma once
#include "GameFramework/Actor.h"
#include "FGEnemy.generated.h"
class UStaticMeshComponent;
class AFGProjectile;
class AFGPawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGPAnimationDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFireProjectile, FVector, EventSourceLocation);

UCLASS(meta = (BlueprintSpawnableComponent))
class AFGEnemy : public AActor
{
	GENERATED_BODY()
public:
	AFGEnemy();

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MovementSpeed;
	UPROPERTY(BlueprintReadOnly)
		float EnemyDirection;
	UPROPERTY(BlueprintReadOnly)
		FVector EnemyVelocity;
	void Stun();
private:
	float LeftEndPosition;
	float RightEndPosition;
	float Timer;
	float AnimTimer;
	float StationaryTimer;
	float StunTimer;
	float MaxSpeed;
	float MinSpeed;
	float Multiplier;
	bool StartedAnimation;
	bool StoppedToShoot;
	bool Fired;
	bool Stunned;
	AActor* Target;
	FVector PlayerDirection;

	UPROPERTY(BlueprintAssignable)
		FGPAnimationDelegate OnAnimationStarted;
	UPROPERTY(BlueprintAssignable)
		FGPAnimationDelegate OnStunAnimationStarted;
	UPROPERTY(BlueprintAssignable)
		FGPAnimationDelegate OnStunAnimationEnded;
	UPROPERTY(BlueprintAssignable)
		FOnFireProjectile OnFireProjectile;
	UPROPERTY(EditAnywhere)
		bool IsMoving;
	UPROPERTY(EditInstanceOnly)
		bool Flipped;
	UPROPERTY(EditAnywhere)
		float SlowDownMultiplier;
	UPROPERTY(EditAnywhere)
		float SpeedUpMultiplier;
	UPROPERTY(EditAnywhere)
		float LeftEndDistance = 0;
	UPROPERTY(EditAnywhere)
		float RightEndDistance = 0;
	UPROPERTY(EditAnywhere)
		float CoolDown;
	UPROPERTY(EditAnywhere)
		float AnimCoolDown;
	UPROPERTY(EditAnywhere)
		float StunDuration;
	UPROPERTY(EditAnywhere)
		float StationaryDuration;
	UPROPERTY(EditAnywhere)
		float ProjectileSpawnLocation;
	UPROPERTY(EditAnywhere)
		float FiringRange;
	UPROPERTY(EditAnywhere)
		float FiringDistance;
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Root;
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Gun;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFGProjectile> ProjectileClass;
	
	void Move(float DeltaSeconds);
	void AimAndFire();
	bool CanAimAtPlayer();
};