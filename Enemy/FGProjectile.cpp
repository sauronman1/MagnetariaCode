#include "FGProjectile.h"
#include "FGEnemy.h"
#include "Components/SphereComponent.h"
#include "GP4_Team10/Player/FGHealthComponent.h"
#include "GP4_Team10/Player/FGPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
//#include "NiagaraFunctionLibrary.h"

AFGProjectile::AFGProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFGProjectile::ProjectileBeginOverlap);
}


void AFGProjectile::BeginPlay()
{
	Super::BeginPlay();
	SpawnInvincibleDuration = 0.5f;
	UMagnetComponent* MagnetComp = FindComponentByClass<UMagnetComponent>();
	if(MagnetComp == nullptr) { return;}
	if(MagnetComp->GetPolarity() == EPolarity::POSITIVE)
	{
		FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, PositiveMaterial);
	}
	else if(MagnetComp->GetPolarity() == EPolarity::NEGATIVE)
	{
		FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, NegativeMaterial);
	}

	OnProjectileSpawned.Broadcast(GetActorLocation());
}

void AFGProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Timer += DeltaSeconds;
	if(Timer > BulletLifetime)
		Destroy();
	if(!IsHit)
		Velocity = GetActorUpVector() * Speed * DeltaSeconds;
	else
		AddForce(DeltaSeconds);

	
	ChasingPlayer();
	AddActorWorldOffset(Velocity, true);
}

void AFGProjectile::ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	if(Timer > SpawnInvincibleDuration)
	{
		AFGPawn* Player = Cast<AFGPawn>(OtherActor);
		AFGEnemy* Enemy = Cast<AFGEnemy>(OtherActor);
	
		if(Player != nullptr)
		{
			UMagnetComponent* MagnetComp = FindComponentByClass<UMagnetComponent>();
			if(MagnetComp == nullptr) { return;}
			if(MagnetComp->GetPolarity() == Player->GetPolarity())
			{
				IsHit = true;
			}
			else
			{
				UFGHealthComponent* PlayerHealthComp = Player->FindComponentByClass<UFGHealthComponent>();
				if(PlayerHealthComp == nullptr) { return;}
				PlayerHealthComp->TakeDamage(Damage);
				//UNiagaraFunctionLibrary::Spawn
				OnProjectileDestroyed.Broadcast(GetActorLocation());
				Destroy();
			}
		}
		else if(Enemy != nullptr && TargetedEnemy)
		{
			Enemy->Stun();
			OnProjectileDestroyed.Broadcast(GetActorLocation());
			Destroy();
		}
		else if(Enemy == nullptr)
		{
			OnProjectileDestroyed.Broadcast(GetActorLocation());
			Destroy();
		}
	}
}





void AFGProjectile::AddForce(float DeltaSeconds)
{
	if(!TargetedEnemy)
	{
		Velocity = Shooter->GetActorLocation() - GetActorLocation();
		TargetedEnemy = true;
		OnProjectileDeflected.Broadcast(GetActorLocation());
	}
	Velocity.Normalize();
	Velocity *= RepelSpeed * DeltaSeconds;
	
}

void AFGProjectile::ChasingPlayer()
{
	float DistToPlayer = FVector::Dist(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation(), GetActorLocation());
	UMagnetComponent* MagnetComp = FindComponentByClass<UMagnetComponent>();
	AFGPawn* Player = Cast<AFGPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if(DistToPlayer < ChasingDistance && MagnetComp->GetPolarity() != Player->GetPolarity())
	{
		FVector Target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation() - GetActorLocation();
		Target.Normalize();
		FRotator Rotation = UKismetMathLibrary::MakeRotFromZ(Target);
		SetActorRotation(Rotation);

	}
}



