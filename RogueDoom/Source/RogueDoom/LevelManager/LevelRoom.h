// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelRoom.generated.h"

UCLASS()
class ROGUEDOOM_API ULevelRoom final : public UObject
{
	GENERATED_BODY()

public:
	
	
private:
	const int SizeX = 7, SizeY = 7;
	int MaxRoomCount;
	int CurrentRoomCount;
	TArray<TArray<bool>> IsRoomArray;
	TArray<TArray<AActor*>> RoomActorArray;
	TArray<FVector2D> Leaf;
	
	FVector2D PlayerRoomPosition;

	UPROPERTY()
	UClass* RoomBlueprint;
	
public:
	void Init();
	void MakeRoom();
	
	void PrintRoom();
	void ClearRoom(const FVector2D Position);
	void ChangeRoom(const FVector2D Position);
	
private:
	bool Check4Direction(const int X,const int Y);
	bool CheckAddRoom(bool& ReturnMakeRoom, const int X,const int Y);
	
	bool Check2Direction(const int X,const int Y);
	bool CheckFullRoom();
	bool CheckRandom();

public:
	FVector2D GetSize()const{return FVector2D(SizeX,SizeY);}
};
