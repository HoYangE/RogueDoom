// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelRoom.h"

#include "RoomActor.h"
#include "RogueDoom/GameManager/RogueDoom.h"

#pragma region Setting
void ULevelRoom::Init()
{
	RoomBlueprint = LoadObject<UClass>(nullptr, TEXT("/Game/BluePrint/RoomActor.RoomActor_C"));

	TArray<bool> BoolTemp;
	BoolTemp.Init(false, SizeX);
	IsRoomArray.Init(BoolTemp, SizeY);
	TArray<AActor*> ActorTemp;
	ActorTemp.Init(nullptr, SizeX);
	RoomActorArray.Init(ActorTemp, SizeY);

	PlayerRoomPosition = FVector2D(SizeX / 2, SizeY / 2);

	IsRoomArray[SizeY/2][SizeX/2] = true;
	CurrentRoomCount = 1;
	
	Leaf.Empty();
	Leaf.Emplace(FVector2D(SizeX/2, SizeY/2));
	
	MaxRoomCount = FMath::RandRange(1,2) + 2 + 5 + 6;
}

void ULevelRoom::PrintRoom()
{
	const FVector CenterPos = FVector(SizeX/2, SizeY/2, 0);
	for (int i = 0; i < SizeY; i++)
	{
		FString Temp;
		for (int j = 0; j < SizeX; j++)
		{
			if (IsRoomArray[i][j] == true)
			{
				const auto RoomActor = GetWorld()->SpawnActor<AActor>(RoomBlueprint, FVector(4000*(i-CenterPos.X),3000*(j-CenterPos.Y),0), FRotator::ZeroRotator);
				const auto RoomClass = Cast<ARoomActor>(RoomActor);
				RoomClass->Position = FVector2D(j,i);
				RoomClass->SetWall(i+1<SizeY?IsRoomArray[i+1][j]:false, j+1<SizeX?IsRoomArray[i][j+1]:false, j-1>=0?IsRoomArray[i][j-1]:false, i-1>=0?IsRoomArray[i-1][j]:false);
				RoomActorArray[i][j] = RoomActor;
			}
		}
	}
}

void ULevelRoom::ClearRoom(const FVector2D Position)
{
	const auto RoomClass = Cast<ARoomActor>(RoomActorArray[Position.Y][Position.X]);
	RoomClass->DeleteAllDoor();
}
void ULevelRoom::ChangeRoom(const FVector2D Position)
{
	const auto PlayingRoomClass = Cast<ARoomActor>(RoomActorArray[Position.Y][Position.X]);
	
	PlayerRoomPosition = Position;
}

#pragma endregion Setting


#pragma region RoomMake
void ULevelRoom::MakeRoom()
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
				if(FMath::RandBool() && Leaf[i].Y - 1 >= 0)
					bMakeRoom = Check4Direction(Leaf[i].X - 1, Leaf[i].Y);
				else if(Leaf[i].X + 1 < SizeX)
					bMakeRoom = Check4Direction(Leaf[i].X + 1, Leaf[i].Y);
			}
			else
			{
				if(FMath::RandBool() && Leaf[i].Y - 1 >= 0)
					bMakeRoom = Check4Direction(Leaf[i].X, Leaf[i].Y - 1);
				else if(Leaf[i].Y + 1 < SizeY)
					bMakeRoom = Check4Direction(Leaf[i].X, Leaf[i].Y + 1);
			}
		}
	}
}

bool ULevelRoom::Check4Direction(const int X, const int Y)
{
	bool ReturnMakeRoom = false;
	if(X >= 0 && Y - 1 >= 0 && !IsRoomArray[Y - 1][X] && !IsRoomArray[Y][X])
	{
		if(CheckAddRoom(ReturnMakeRoom, X,Y))
			Leaf.Remove(FVector2D(X,Y+1));
	}
	if(X >= 0 && Y + 1 < SizeY && !IsRoomArray[Y + 1][X] && !IsRoomArray[Y][X])
	{
		if(CheckAddRoom(ReturnMakeRoom, X,Y))
			Leaf.Remove(FVector2D(X,Y-1));
	}
	if(X - 1 >= 0 && Y >= 0 && !IsRoomArray[Y][X - 1] && !IsRoomArray[Y][X])
	{
		if(CheckAddRoom(ReturnMakeRoom, X,Y))
			Leaf.Remove(FVector2D(X+1,Y));
	}
	if(X + 1 < SizeX && Y >= 0 && !IsRoomArray[Y][X + 1] && !IsRoomArray[Y][X])
	{
		if(CheckAddRoom(ReturnMakeRoom, X,Y))
			Leaf.Remove(FVector2D(X-1,Y));
	}
	return ReturnMakeRoom;
}

bool ULevelRoom::CheckAddRoom(bool& ReturnMakeRoom, const int X, const int Y)
{
	if(Check2Direction(X, Y) && !CheckFullRoom() && CheckRandom())
	{
		IsRoomArray[Y][X] = true;
		Leaf.Emplace(FVector2D(X,Y));
		CurrentRoomCount++;
		ReturnMakeRoom = true;
	}
	return ReturnMakeRoom;
}

bool ULevelRoom::Check2Direction(const int X, const int Y)
{
	int Count = 0;
	if(Y - 1 >= 0 && IsRoomArray[Y - 1][X])
		Count++;
	if(Y + 1 < SizeY && IsRoomArray[Y + 1][X])
		Count++;
	if(X - 1 >= 0 && IsRoomArray[Y][X - 1])
		Count++;
	if(X + 1 < SizeX && IsRoomArray[Y][X + 1])
		Count++;
	if(Count >= 2)
		return false;
	return true;
}

bool ULevelRoom::CheckFullRoom()
{
	return CurrentRoomCount == MaxRoomCount;
}

bool ULevelRoom::CheckRandom()
{
	return FMath::RandBool();
}
#pragma endregion RoomMake
