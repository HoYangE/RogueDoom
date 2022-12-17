// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelRoomSearchTree.h"

#include "RogueDoom/GameManager/RogueDoom.h"

void ULevelRoomSearchTree::Init()
{
	RoomActor = LoadObject<UClass>(nullptr, TEXT("/Game/BluePrint/Room.Room_C"));

	TArray<bool> Temp;
	Temp.Init(false, SizeX);
	Room.Init(Temp, SizeY);
	
	Room[SizeY/2][SizeX/2] = true;
	CurrentRoomCount = 1;
	
	Leaf.Empty();
	Leaf.Emplace(MakeTuple(SizeY/2, SizeX/2));

	MaxRoomCount = FMath::RandRange(1,2) + 2 + 5 + 6;
}

void ULevelRoomSearchTree::PrintRoom()
{
	const FVector CenterPos = FVector(SizeX/2, SizeY/2, 0);
	for (int i = 0; i < SizeY; i++)
	{
		FString Temp;
		for (int j = 0; j < SizeX; j++)
		{
			if (Room[i][j] == true)
			{
				//Temp += "1 ";
				GetWorld()->SpawnActor<AActor>(RoomActor, FVector(4000*(i-CenterPos.X),3000*(j-CenterPos.Y),0), FRotator::ZeroRotator);
			}
			//else
				//Temp += "0 ";
		}
		//ROGUEDOOM(Warning,TEXT("%s"),*Temp);
	}
	//ROGUEDOOM(Warning,TEXT("%d"),CurrentRoomCount);
}

void ULevelRoomSearchTree::MakeRoom()
{
	int MaxCount = 0;
	bool bMakeRoom = false;
	while(CurrentRoomCount != MaxRoomCount)
	{
		if(bMakeRoom == false)
		{
			MaxCount++;
			if(MaxCount > 30)
			{
				Init();
				MakeRoom();
				break;
			}
		}
		
		for(int i = 0; i < Leaf.Num(); i++)
		{
			if(FMath::RandBool())
			{
				if(FMath::RandBool() && Leaf[i].Get<0>() - 1 >= 0)
					bMakeRoom = Check4Direction(Leaf[i].Get<1>(), Leaf[i].Get<0>() - 1);
				else if(Leaf[i].Get<0>() + 1 < SizeX)
					bMakeRoom = Check4Direction(Leaf[i].Get<1>(), Leaf[i].Get<0>() + 1);
			}
			else
			{
				if(FMath::RandBool() && Leaf[i].Get<1>() - 1 >= 0)
					bMakeRoom = Check4Direction(Leaf[i].Get<1>() - 1, Leaf[i].Get<0>());
				else if(Leaf[i].Get<1>() + 1 < SizeY)
					bMakeRoom = Check4Direction(Leaf[i].Get<1>() + 1, Leaf[i].Get<0>());
			}
		}
	}
}

bool ULevelRoomSearchTree::Check4Direction(const int X, const int Y)
{
	bool ReturnMakeRoom = false;
	if(Y - 1 >= 0 && !Room[Y - 1][X] && !Room[Y][X])
	{
		if(CheckAddRoom(ReturnMakeRoom, X,Y))
			Leaf.Remove(MakeTuple(Y+1, X));
	}
	if(Y + 1 < SizeY && !Room[Y + 1][X] && !Room[Y][X])
	{
		if(CheckAddRoom(ReturnMakeRoom, X,Y))
			Leaf.Remove(MakeTuple(Y-1, X));
	}
	if(X - 1 >= 0 && !Room[Y][X - 1] && !Room[Y][X])
	{
		if(CheckAddRoom(ReturnMakeRoom, X,Y))
			Leaf.Remove(MakeTuple(Y, X+1));
	}
	if(X + 1 < SizeX && !Room[Y][X + 1] && !Room[Y][X])
	{
		if(CheckAddRoom(ReturnMakeRoom, X,Y))
			Leaf.Remove(MakeTuple(Y, X-1));
	}
	return ReturnMakeRoom;
}

bool ULevelRoomSearchTree::CheckAddRoom(bool& ReturnMakeRoom, const int X, const int Y)
{
	if(Check2Direction(X, Y) && !CheckFullRoom() && CheckRandom())
	{
		Room[Y][X] = true;
		Leaf.Emplace(MakeTuple(Y,X));
		CurrentRoomCount++;
		ReturnMakeRoom = true;
	}
	return ReturnMakeRoom;
}

bool ULevelRoomSearchTree::Check2Direction(const int X, const int Y)
{
	int Count = 0;
	if(Y - 1 >= 0 && Room[Y - 1][X])
		Count++;
	if(Y + 1 < SizeY && Room[Y + 1][X])
		Count++;
	if(X - 1 >= 0 && Room[Y][X - 1])
		Count++;
	if(X + 1 < SizeX && Room[Y][X + 1])
		Count++;
	if(Count >= 2)
		return false;
	return true;
}

bool ULevelRoomSearchTree::CheckFullRoom()
{
	return CurrentRoomCount == MaxRoomCount;
}

bool ULevelRoomSearchTree::CheckRandom()
{
	return FMath::RandBool();
}
