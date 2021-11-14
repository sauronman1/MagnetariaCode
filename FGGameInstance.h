#pragma once

#include "Engine/GameInstance.h"
#include "FGGameinstance.generated.h"
class UFGMainSaveGame;
UCLASS()
class UFGGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	bool IsNewGame();
	bool SaveGame();
	UFUNCTION(BlueprintCallable)
		bool CreateNewSaveGame();
	UFUNCTION(BlueprintCallable)
		bool LoadGame();
	
	UPROPERTY()
		UFGMainSaveGame* CurrentSaveGame;
private:
	//TODO Consider replacing static string
	static const FString UNIQUE_SAVE_SLOT;
	
};