#pragma once
#include "GameFramework/Actor.h"
#include "FGCheckPoint.generated.h"
class UBoxComponent;

UCLASS()
class AFGCheckPoint : public AActor
{
	GENERATED_BODY()
public:
	AFGCheckPoint();
	void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* BoxComp;

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit);
};