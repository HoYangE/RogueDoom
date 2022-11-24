// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RogueDoomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROGUEDOOM_API URogueDoomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	
private:
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	
public:
	APlayerCharacter* GetPlayerCharacter()const{return PlayerCharacter;}
	void SetPlayerCharacter(APlayerCharacter* NewPlayerCharacter){PlayerCharacter = NewPlayerCharacter;}
	

private:
	
};
