#include "FGCheckPoint.h"

#include "FGMainSaveGame.h"
#include "Components/BoxComponent.h"
#include "GP4_Team10/FGGameInstance.h"
#include "GP4_Team10/Enemy/FGEnemy.h"
#include "GP4_Team10/Player/FGPawn.h"
#include "Kismet/GameplayStatics.h"

AFGCheckPoint::AFGCheckPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFGCheckPoint::HandleBeginOverlap);
}

void AFGCheckPoint::BeginPlay()
{
	
	
}


void AFGCheckPoint::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	AFGPawn* Player = Cast<AFGPawn>(OtherActor);
	if(Player != nullptr)
	{
		UFGGameInstance* GameInstance = Cast<UFGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if(GameInstance->CurrentSaveGame != nullptr)
			GameInstance->CurrentSaveGame->LastSavedCheckpoint.CheckPointLocation = OtherActor->GetActorLocation();
		GameInstance->SaveGame();
	}
}

