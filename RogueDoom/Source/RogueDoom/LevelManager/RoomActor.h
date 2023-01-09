// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.generated.h"

class UMaterialInstanceConstant;
class ARoomActor;

UENUM(BluePrintType)
enum class EWallType :uint8
{
	Wall = 0   UMETA(DisplayName = "Wall"),
	Door  UMETA(DisplayName = "Door")
};

UCLASS()
class ROGUEDOOM_API AWallActor final : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Wall, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	UMaterialInstanceConstant* WallMaterial;
	UPROPERTY()
	UMaterialInstanceConstant* DoorMaterial;
	
	FVector2D RoomPosition;

private:
	UPROPERTY()
	UStaticMesh* WallMesh;

public:
	void InitRoom(const FVector2D Position);
	void InitMesh(const EWallType WallType, const FVector Location, const FVector Scale)const;
	void DeleteDoor()const;
	
private:
	AWallActor();
	
	void MakeWall(UStaticMeshComponent* Wall)const;
	void MakeDoor(UStaticMeshComponent* Wall)const;
};

UCLASS()
class ROGUEDOOM_API ARoomActor final : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Wall, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Floor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Wall, meta = (AllowPrivateAccess = "true"))
	AWallActor* NWall;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Wall, meta = (AllowPrivateAccess = "true"))
	AWallActor* EWall;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Wall, meta = (AllowPrivateAccess = "true"))
	AWallActor* WWall;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Wall, meta = (AllowPrivateAccess = "true"))
	AWallActor* SWall;
	
	FVector2D Position;

private:
	float FloorSizeX, FloorSizeY;

public:	
	void SetWall(const bool N,const bool E,const bool W,const bool S);
	void DeleteAllDoor()const;
	TArray<AWallActor*> GetAllWall()const;
	TArray<AWallActor*> GetAllDoor()const;
	
private:
	ARoomActor();
	void InitMesh();
	AWallActor* MakeWall(bool IsDoor, FName Direction);
};
