#include "FGMainSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UFGMainSaveGame::CreateSlot(const FString& SlotName)
{
	SaveGameName = SlotName;
	CreationTime = FDateTime::Now();
	DefaultSaveData.CheckPointLocation = FVector::ZeroVector;
	LastSavedCheckpoint = DefaultSaveData;
}
