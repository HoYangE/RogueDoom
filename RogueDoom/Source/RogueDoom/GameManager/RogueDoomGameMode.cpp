// Copyright Epic Games, Inc. All Rights Reserved.

#include "RogueDoomGameMode.h"
#include "RogueDoom/Player/PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARogueDoomGameMode::ARogueDoomGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APlayerCharacter> PlayerPawnBPClass(TEXT("/Game/BluePrint/BP_PlayerCharacter.BP_PlayerCharacter_C"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	//DefaultPawnClass = APlayerCharacter::StaticClass();
}
