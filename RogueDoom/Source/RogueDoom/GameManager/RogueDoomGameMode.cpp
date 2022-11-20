// Copyright Epic Games, Inc. All Rights Reserved.

#include "RogueDoomGameMode.h"
#include "RogueDoom/Player/PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARogueDoomGameMode::ARogueDoomGameMode()
{
	if (const ConstructorHelpers::FClassFinder<APlayerCharacter> PlayerPawnBPClass(TEXT("/Game/BluePrint/BP_PlayerCharacter.BP_PlayerCharacter_C")); PlayerPawnBPClass.Class)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}	
	//DefaultPawnClass = APlayerCharacter::StaticClass();
}
