// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueDoomGameInstance.h"

#include "RogueDoom/LevelManager/LevelRoomSearchTree.h"

URogueDoomGameInstance::URogueDoomGameInstance()
{
	Map = CreateDefaultSubobject<ULevelRoomSearchTree>(TEXT("Tree"));
}


void URogueDoomGameInstance::Init()
{
	Super::Init();

	const auto Tree = Cast<ULevelRoomSearchTree>(Map);
	Tree->Init();
	Tree->MakeRoom();
	Tree->PrintRoom();
}