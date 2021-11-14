#pragma once

#include "GameFramework/SaveGame.h"
#include "FGMainSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FSaveData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector CheckPointLocation;
};

UCLASS()
class UFGMainSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString SaveGameName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FDateTime CreationTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FSaveData LastSavedCheckpoint;

	FSaveData DefaultSaveData;
	void CreateSlot(const FString& SlotName);
};

