// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "RogueDoom/GameManager/RogueDoom.h"

#include "Accessory.generated.h"

class UGunWeapon;
USTRUCT(Atomic, BlueprintType)
struct FAccessoryData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString Info;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FTransform Transform;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName SocketName;
};

UINTERFACE()
class UAccessoryInterface : public UInterface
{
	GENERATED_BODY()
};
class IAccessoryInterface
{
	GENERATED_BODY()
public:
	virtual FAccessoryData GetAccessoryData() = 0;
};

UCLASS()
class ROGUEDOOM_API UAccessoryDecorator : public UStaticMeshComponent, public IAccessoryInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FAccessoryData Data;
	
public:
	virtual FAccessoryData GetAccessoryData() override { return Data; }
};

UCLASS()
class ROGUEDOOM_API UTopRedDotScope1 final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	virtual FAccessoryData GetAccessoryData() override;
};
UCLASS()
class ROGUEDOOM_API UTopRedDotScope2 final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	virtual FAccessoryData GetAccessoryData() override;
};
UCLASS()
class ROGUEDOOM_API UTopRedDotScope3 final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	virtual FAccessoryData GetAccessoryData() override;
};
UCLASS()
class ROGUEDOOM_API UBottomAngledGrip final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	virtual FAccessoryData GetAccessoryData() override;
};
UCLASS()
class ROGUEDOOM_API UForwardFlashHider final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	virtual FAccessoryData GetAccessoryData() override;
};
UCLASS()
class ROGUEDOOM_API UForwardSilencer final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	virtual FAccessoryData GetAccessoryData() override;
};