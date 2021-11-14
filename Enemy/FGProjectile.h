#pragma once
#include "GP4_Team10/Gameplay/Magnet.h"
#include "FGProjectile.generated.h"
class AFGEnemy;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileSpawned, FVector, EventSourceLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileDestroyed, FVector, EventSourceLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileDeflected, FVector, EventSourceLocation);

UCLASS()
class AFGProjectile : public AMagnet
{
	GENERATED_BODY()
public:
	AFGProjectile();
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	AFGEnemy* Shooter;

	UPROPERTY(BlueprintAssignable)
	FOnProjectileSpawned OnProjectileSpawned;

	UPROPERTY(BlueprintAssignable)
	FOnProjectileDestroyed OnProjectileDestroyed;

	UPROPERTY(BlueprintAssignable)
	FOnProjectileDeflected OnProjectileDeflected;

private:
	float SpawnInvincibleDuration;
	float Timer;
	FVector Velocity;
	bool IsHit;
	bool TargetedEnemy;
	UPROPERTY(VisibleAnywhere)
		USphereComponent* SphereComp;
	UPROPERTY(EditDefaultsOnly)
		float BulletLifetime;
	UPROPERTY(EditDefaultsOnly)
		float Speed;
	UPROPERTY(EditDefaultsOnly)
		float RepelSpeed;
	UPROPERTY(EditDefaultsOnly)
		float Damage;
	UPROPERTY(EditDefaultsOnly)
		float ChasingDistance;
	UPROPERTY(EditDefaultsOnly)
		UMaterial* PositiveMaterial;
	UPROPERTY(EditDefaultsOnly)
		UMaterial* NegativeMaterial;
	
	UFUNCTION()
	void ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit);
	void AddForce(float DeltaSeconds);
	void ChasingPlayer();
};