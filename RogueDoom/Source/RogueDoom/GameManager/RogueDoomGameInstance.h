// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RogueDoomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROGUEDOOM_API URogueDoomGameInstance final : public UGameInstance
{
	GENERATED_BODY()

public:
	
private:
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;
	UPROPERTY()
	UObject* Map;

	FVector2D CurrentRoomPosition;
	
public:
	URogueDoomGameInstance();
	virtual void Init() override;

	APlayerCharacter* GetPlayerCharacter()const{return PlayerCharacter;}
	void SetPlayerCharacter(APlayerCharacter* NewPlayerCharacter){PlayerCharacter = NewPlayerCharacter;}
	void ClearRoom(const FVector2D RoomPosition)const;
	void ChangeRoom(const FVector2D RoomPosition);

private:
	
};
