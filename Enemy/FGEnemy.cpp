#include "FGEnemy.h"
#include "FGProjectile.h"
#include "GP4_Team10/Player/FGPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AFGEnemy::AFGEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	Gun = CreateDefaultSubobject<UStaticMeshComponent>("Gun");
	Gun->SetupAttachment(Root);
	RootComponent = Root;
}

void AFGEnemy::BeginPlay()
{
	Super::BeginPlay();
	LeftEndPosition = GetActorLocation().Y - LeftEndDistance;
	RightEndPosition = GetActorLocation().Y + RightEndDistance;
	EnemyDirection = 1;
	MaxSpeed = MovementSpeed;
	MinSpeed = 10;
	Multiplier = 1;
	Target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AFGEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Timer += DeltaSeconds;
	AnimTimer += DeltaSeconds;
	StationaryTimer += DeltaSeconds;
	StunTimer += DeltaSeconds;
	Move(DeltaSeconds);
	AimAndFire();


}

void AFGEnemy::Move(float DeltaSeconds)
{
	if(IsMoving && !StoppedToShoot && !Stunned)
	{
		if((RightEndPosition - GetActorLocation().Y < 100.f && EnemyDirection == 1)|| (LeftEndPosition - GetActorLocation().Y > -100.f && EnemyDirection == -1))
		{
			Multiplier = SlowDownMultiplier;
		}

		if(LeftEndPosition - GetActorLocation().Y > -10.f)
		{
			SetActorRotation(FRotator(0,0,0));
			EnemyDirection = 1;
			Flipped = false;
			Multiplier = SpeedUpMultiplier;
		}
		else if (RightEndPosition - GetActorLocation().Y < 10.f)
		{
			SetActorRotation(FRotator(0,-180,0));
			EnemyDirection = -1;
			Flipped = true;
			Multiplier = SpeedUpMultiplier;
		}

		MovementSpeed *= Multiplier;
		MovementSpeed = FMath::Clamp<float>(MovementSpeed, MinSpeed, MaxSpeed);
		EnemyVelocity = GetActorRightVector()  * MovementSpeed * DeltaSeconds;
		AddActorWorldOffset(GetActorRightVector()  * MovementSpeed * DeltaSeconds);

	}
	else
	{
		EnemyVelocity = FVector(0,0,0);
	}
}

void AFGEnemy::AimAndFire()
{
	if(!Stunned)
	{
		if(CanAimAtPlayer())
		{
			if(Target == nullptr) {return;}
	
			PlayerDirection = Target->GetActorLocation() - GetActorLocation();
			PlayerDirection.Normalize();
			FRotator Rotation;
			if(Flipped)
				Rotation = UKismetMathLibrary::MakeRotFromZ(FVector(PlayerDirection.X, -PlayerDirection.Y, PlayerDirection.Z));
			else
				Rotation = UKismetMathLibrary::MakeRotFromZ(FVector(PlayerDirection.X, PlayerDirection.Y, PlayerDirection.Z));
			Gun->SetRelativeRotation(Rotation);

			if(AnimTimer > AnimCoolDown && !StartedAnimation)
			{
				OnAnimationStarted.Broadcast();
				StartedAnimation = true;
				StationaryTimer = 0;
				StoppedToShoot = true;
				//Fired = false;
			}

			// if(StationaryTimer < StationaryDuration)
			// {
			// 	StoppedToShoot = true;
			// }
			// else if(!Fired)
			// {
			// 	StoppedToShoot = false;
			// 	Fired = true;
			// }
	
			if(Timer > CoolDown)
			{
				FTransform SpawnTransform;
				SpawnTransform.SetLocation(Gun->GetComponentLocation() + Gun->GetUpVector() * ProjectileSpawnLocation);
				SpawnTransform.SetRotation(Gun->GetComponentRotation().Quaternion());
				AFGProjectile* Projectile = GetWorld()->SpawnActor<AFGProjectile>(ProjectileClass, SpawnTransform);
				Projectile->Shooter = this;
				StartedAnimation = false;
				AnimTimer = 0;
				Timer = 0;
				OnFireProjectile.Broadcast(GetActorLocation());
			}
		}
		else
		{
			StoppedToShoot = false;
			Fired = true;
			StartedAnimation = false;
			//AnimTimer = 0;
			//Timer = 0;
		}
	}
	else
	{
		if(StunTimer > StunDuration)
		{
			OnStunAnimationEnded.Broadcast();
			StoppedToShoot = false;
			Fired = true;
			StartedAnimation = false;
			AnimTimer = 0;
			Timer = 0;
			StationaryTimer = 0;
			Stunned = false;
		}
	}
}

bool AFGEnemy::CanAimAtPlayer()
{
	float Distance = FVector::Dist(Target->GetActorLocation(), GetActorLocation());
	if(Distance < FiringDistance)
	{
		FVector Direction = Target->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
		float DotProduct = FVector::DotProduct(Direction, GetActorRightVector());
		if(DotProduct > FiringRange)
			return true;
	}
	return false;

}

void AFGEnemy::Stun()
{
	OnStunAnimationStarted.Broadcast();
	Stunned = true;
	StunTimer = 0;
}




