// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Accessory.h"
#include "Components/SkeletalMeshComponent.h"

#include "GunWeapon.generated.h"


class UGunWeapon;
USTRUCT(Atomic, BlueprintType)
struct FGunData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USkeletalMesh* Mesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString Info;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FTransform Transform;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DelayTime;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MaxBullet;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int CurrentBullet;
};

UINTERFACE()
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};
class IWeaponInterface
{
	GENERATED_BODY()
public:
	virtual void InitSetting() = 0;
	virtual void Display() = 0;
	virtual void Fire(const FTransform Muzzle) = 0;
};

UCLASS()
class ROGUEDOOM_API AWeapon : public AActor
{
	GENERATED_BODY()
public:
	AWeapon();
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UGunWeapon* GunWeapon;
	UPROPERTY()
	UAccessoryDecorator* ScopeAccessory;
	UPROPERTY()
	UAccessoryDecorator* LeftHandAccessory;
	UPROPERTY()
	UAccessoryDecorator* MuzzleAccessory;
public:
	//virtual void Fire(const FTransform Muzzle);
};

UCLASS()
class ROGUEDOOM_API UGunWeapon : public USkeletalMeshComponent, public IWeaponInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGunData Data;

private:
	bool ShootAble = true;
	FTimerHandle ShootTimerHandle;
	
public:
	virtual void InitSetting() override {}
	virtual void Display() override {}
	virtual void Fire(const FTransform Muzzle) override;
};

UCLASS()
class ROGUEDOOM_API URifleWeapon final : public UGunWeapon
{
	GENERATED_BODY()

public:
	
public:	
	URifleWeapon();

	virtual void InitSetting() override;
	virtual void Display() override {}
	virtual void Fire(const FTransform Muzzle) override;
};