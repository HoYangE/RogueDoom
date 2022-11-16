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

UCLASS()
class ROGUEDOOM_API AWeapon : public AActor
{
	GENERATED_BODY()
public:
	AWeapon();
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UGunWeapon* GunWeapon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAccessoryDecorator* Accessory;
public:
	//virtual void Fire(const FTransform Muzzle);
};

UCLASS()
class ROGUEDOOM_API UGunWeapon : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGunData Data;

private:
	bool ShootAble = true;
	FTimerHandle ShootTimerHandle;
	
public:
	virtual void InitSetting(){};
	virtual void Display() PURE_VIRTUAL(UGunWeapon::InitSetting,);
	virtual void Fire(const FTransform Muzzle);
};

UCLASS()
class ROGUEDOOM_API URifleWeapon final : public UGunWeapon
{
	GENERATED_BODY()

public:
	
public:	
	URifleWeapon();

	virtual void InitSetting() override;
	virtual void Display() override{};
	virtual void Fire(const FTransform Muzzle) override;
};