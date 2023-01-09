// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueDoomGameInstance.h"

#include "RogueDoom/LevelManager/LevelRoom.h"

URogueDoomGameInstance::URogueDoomGameInstance()
{
	Map = CreateDefaultSubobject<ULevelRoom>(TEXT("Tree"));
}


void URogueDoomGameInstance::Init()
{
	Super::Init();

	const auto Tree = Cast<ULevelRoom>(Map);
	Tree->Init();
	Tree->MakeRoom();
	Tree->PrintRoom();
	ChangeRoom(Tree->GetSize() / 2);
}
void URogueDoomGameInstance::ClearRoom(const FVector2D RoomPosition)const
{
	const auto Tree = Cast<ULevelRoom>(Map);
	Tree->ClearRoom(RoomPosition);
}
void URogueDoomGameInstance::ChangeRoom(const FVector2D RoomPosition)
{
	CurrentRoomPosition = RoomPosition;
	ClearRoom(RoomPosition);
	const auto Tree = Cast<ULevelRoom>(Map);
	Tree->ChangeRoom(RoomPosition);
}
