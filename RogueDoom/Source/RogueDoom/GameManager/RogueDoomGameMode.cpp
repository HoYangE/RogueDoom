// Copyright Epic Games, Inc. All Rights Reserved.

#include "RogueDoomGameMode.h"

#include "Blueprint/UserWidget.h"
#include "RogueDoom/Player/PlayerCharacter.h"
#include "RogueDoom/Player/PlayerCharacterController.h"
#include "UObject/ConstructorHelpers.h"

ARogueDoomGameMode::ARogueDoomGameMode()
{
	if (const ConstructorHelpers::FClassFinder<APlayerCharacter> PlayerPawnBP(TEXT("/Game/BluePrint/BP_PlayerCharacter.BP_PlayerCharacter_C")); PlayerPawnBP.Class)
	{
		DefaultPawnClass = PlayerPawnBP.Class;
	}
	PlayerControllerClass = APlayerCharacterController::StaticClass();
	if (const ConstructorHelpers::FClassFinder<UUserWidget> WidgetBP(TEXT("/Game/BluePrint/BP_Widget.BP_Widget_C")); WidgetBP.Class)
	{
		HUDClass = WidgetBP.Class;
	}
	//DefaultPawnClass = APlayerCharacter::StaticClass();
}
