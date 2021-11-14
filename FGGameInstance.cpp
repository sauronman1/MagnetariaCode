#include "FGGameInstance.h"

#include "FGSaveSystem/FGMainSaveGame.h"
#include "Kismet/GameplayStatics.h"

const FString UFGGameInstance::UNIQUE_SAVE_SLOT = "SaveData_0";

bool UFGGameInstance::IsNewGame()
{
	//TODO Function maybe can be removed
	if(UGameplayStatics::DoesSaveGameExist(UNIQUE_SAVE_SLOT, 0))
	{
		return false;
	}
	return true;
}

bool UFGGameInstance::CreateNewSaveGame()
{
	if(CurrentSaveGame == nullptr)
	{
		USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(UFGMainSaveGame::StaticClass());

		if(NewSaveGame != nullptr)
		{
			CurrentSaveGame = Cast<UFGMainSaveGame>(NewSaveGame);
			CurrentSaveGame->LastSavedCheckpoint.CheckPointLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
			UE_LOG(LogTemp, Warning, TEXT("[UFGGameInstance::LoadGame] Success Creatiing Save %s"), *UNIQUE_SAVE_SLOT);
		}
	}
	else
	{
		CurrentSaveGame->CreateSlot(UNIQUE_SAVE_SLOT);
	}

	return UGameplayStatics::SaveGameToSlot(CurrentSaveGame, UNIQUE_SAVE_SLOT, 0);
}

bool UFGGameInstance::LoadGame()
{
	CurrentSaveGame = nullptr;

	
	USaveGame* Slot = UGameplayStatics::LoadGameFromSlot(UNIQUE_SAVE_SLOT, 0);
	if(Slot != nullptr)
	{
		CurrentSaveGame = Cast<UFGMainSaveGame>(Slot);

		if(CurrentSaveGame != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("[UFGGameInstance::LoadGame] Success loading %s"), *UNIQUE_SAVE_SLOT);

			return true;
		}
	}
	return false;
}

bool UFGGameInstance::SaveGame()
{
	if(CurrentSaveGame != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UFGGameInstance::LoadGame] Success saving %s"), *UNIQUE_SAVE_SLOT);
		return UGameplayStatics::SaveGameToSlot(CurrentSaveGame, UNIQUE_SAVE_SLOT, 0);
	}
	return false;
}


