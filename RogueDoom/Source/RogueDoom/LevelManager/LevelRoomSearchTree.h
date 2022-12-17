// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelRoomSearchTree.generated.h"

UCLASS()
class ROGUEDOOM_API ULevelRoomSearchTree: public UObject
{
	GENERATED_BODY()

public:
	
	
private:
	const int SizeX = 7, SizeY = 7;
	int MaxRoomCount;
	int CurrentRoomCount;
	TArray<TArray<bool>> Room;
	TArray<TPair<int,int>> Leaf;

	UPROPERTY()
	UClass* RoomActor;
	
public:
	void Init();
	void MakeRoom();
	
	void PrintRoom();

private:
	bool Check4Direction(const int X,const int Y);
	bool CheckAddRoom(bool& ReturnMakeRoom, const int X,const int Y);
	
	bool Check2Direction(const int X,const int Y);
	bool CheckFullRoom();
	bool CheckRandom();	
};
