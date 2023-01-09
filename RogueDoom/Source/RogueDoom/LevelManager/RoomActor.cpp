// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomActor.h"
#include "Materials/MaterialInstanceConstant.h"

#pragma region Wall
AWallActor::AWallActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	if(const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Wall(TEXT("/Engine/BasicShapes/Cube.Cube")); SM_Wall.Succeeded())
		WallMesh = SM_Wall.Object;
	if(const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_Floor(TEXT("/Game/StartData/LevelPrototyping/Materials/MI_PrototypeGrid_Gray.MI_PrototypeGrid_Gray")); MI_Floor.Succeeded())
		WallMaterial = MI_Floor.Object;
	if(const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_Door(TEXT("/Game/StartData/LevelPrototyping/Materials/MI_Solid_Blue.MI_Solid_Blue")); MI_Door.Succeeded())
		DoorMaterial = MI_Door.Object;
}
void AWallActor::InitRoom(const FVector2D Position)
{
	RoomPosition = Position;
}
void AWallActor::InitMesh(const EWallType WallType, const FVector Location, const FVector Scale)const
{
	WallType==EWallType::Wall?MakeWall(Mesh):MakeDoor(Mesh);

	Mesh->SetRelativeLocation(Location);

	Mesh->SetWorldScale3D(Scale);
}
void AWallActor::MakeWall(UStaticMeshComponent* Wall)const
{
	Wall->SetStaticMesh(WallMesh);
	Wall->SetMaterial(0,WallMaterial);
}
void AWallActor::MakeDoor(UStaticMeshComponent* Wall)const
{
	Wall->SetStaticMesh(WallMesh);
	Wall->SetMaterial(0,DoorMaterial);
}
void AWallActor::DeleteDoor()const
{
	if(Mesh->GetMaterial(0) == DoorMaterial)
		Mesh->SetStaticMesh(nullptr);
}
#pragma endregion Wall


#pragma region Room
ARoomActor::ARoomActor()
{
	InitMesh();
}

void ARoomActor::InitMesh()
{
	FloorSizeX = 40.0f;
	FloorSizeY = 30.0f;
	
	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	SetRootComponent(Floor);
	
	if(const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Floor(TEXT("/Engine/BasicShapes/Plane.Plane")); SM_Floor.Succeeded())
	{
		Floor->SetStaticMesh(SM_Floor.Object);
		Floor->SetRelativeScale3D(FVector(FloorSizeX,FloorSizeY,1.0f));
		if(const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_Floor(TEXT("/Game/StartData/LevelPrototyping/Materials/MI_PrototypeGrid_TopDark.MI_PrototypeGrid_TopDark")); MI_Floor.Succeeded())
			Floor->SetMaterial(0,MI_Floor.Object);
	}
}

void ARoomActor::SetWall(const bool N,const bool E,const bool W,const bool S)
{
	if(NWall == nullptr)
		NWall = MakeWall(N,FName("N"));
	if(EWall == nullptr)
		EWall = MakeWall(E,FName("E"));
	if(WWall == nullptr)
		WWall = MakeWall(W,FName("W"));
	if(SWall == nullptr)
		SWall = MakeWall(S,FName("S"));
}

AWallActor* ARoomActor::MakeWall(const bool IsDoor, const FName Direction)
{
	const auto WallActor = GetWorld()->SpawnActor(AWallActor::StaticClass());
	const auto WallClass = Cast<AWallActor>(WallActor);
	const bool IsNorthOrSouth = Direction==FName("N")||Direction==FName("S");

	constexpr int WallHeight = 10;
	
	FVector Location = FVector::ZeroVector;
	if(Direction==FName("N"))
		Location = GetActorLocation()+GetActorForwardVector()*FloorSizeX/2*100+GetActorUpVector()*WallHeight/2*100;
	else if(Direction==FName("E"))
		Location = GetActorLocation()+GetActorRightVector()*FloorSizeY/2*100+GetActorUpVector()*WallHeight/2*100;
	else if(Direction==FName("W"))
		Location = GetActorLocation()-GetActorRightVector()*FloorSizeY/2*100+GetActorUpVector()*WallHeight/2*100;
	else if(Direction==FName("S"))
		Location = GetActorLocation()-GetActorForwardVector()*FloorSizeX/2*100+GetActorUpVector()*WallHeight/2*100;

	WallClass->InitRoom(Position);
	WallClass->InitMesh(IsDoor?EWallType::Door:EWallType::Wall, Location,
		IsNorthOrSouth?FVector(0.001f,FloorSizeY,WallHeight):FVector(FloorSizeX,0.001f,WallHeight));

	return WallClass;
}

void ARoomActor::DeleteAllDoor()const
{
	if(const auto WallClass = Cast<AWallActor>(NWall); WallClass->Mesh->GetMaterial(0) == WallClass->DoorMaterial)
		WallClass->Mesh->SetStaticMesh(nullptr);
	if(const auto WallClass = Cast<AWallActor>(EWall); WallClass->Mesh->GetMaterial(0) == WallClass->DoorMaterial)
		WallClass->Mesh->SetStaticMesh(nullptr);
	if(const auto WallClass = Cast<AWallActor>(WWall); WallClass->Mesh->GetMaterial(0) == WallClass->DoorMaterial)
		WallClass->Mesh->SetStaticMesh(nullptr);
	if(const auto WallClass = Cast<AWallActor>(SWall); WallClass->Mesh->GetMaterial(0) == WallClass->DoorMaterial)
		WallClass->Mesh->SetStaticMesh(nullptr);
}

TArray<AWallActor*> ARoomActor::GetAllWall()const
{
	TArray<AWallActor*> Temp;
	Temp.Empty();
	if(const auto WallClass = Cast<AWallActor>(NWall); WallClass->Mesh->GetMaterial(0) == WallClass->WallMaterial)
		Temp.Add(WallClass);
	if(const auto WallClass = Cast<AWallActor>(EWall); WallClass->Mesh->GetMaterial(0) == WallClass->WallMaterial)
		Temp.Add(WallClass);
	if(const auto WallClass = Cast<AWallActor>(WWall); WallClass->Mesh->GetMaterial(0) == WallClass->WallMaterial)
		Temp.Add(WallClass);
	if(const auto WallClass = Cast<AWallActor>(SWall); WallClass->Mesh->GetMaterial(0) == WallClass->WallMaterial)
		Temp.Add(WallClass);
	return Temp;
}
TArray<AWallActor*> ARoomActor::GetAllDoor()const
{
	TArray<AWallActor*> Temp;
	Temp.Empty();
	if(const auto WallClass = Cast<AWallActor>(NWall); WallClass->Mesh->GetMaterial(0) == WallClass->DoorMaterial)
		Temp.Add(WallClass);
	if(const auto WallClass = Cast<AWallActor>(EWall); WallClass->Mesh->GetMaterial(0) == WallClass->DoorMaterial)
		Temp.Add(WallClass);
	if(const auto WallClass = Cast<AWallActor>(WWall); WallClass->Mesh->GetMaterial(0) == WallClass->DoorMaterial)
		Temp.Add(WallClass);
	if(const auto WallClass = Cast<AWallActor>(SWall); WallClass->Mesh->GetMaterial(0) == WallClass->DoorMaterial)
		Temp.Add(WallClass);
	return Temp;
}
#pragma endregion Room