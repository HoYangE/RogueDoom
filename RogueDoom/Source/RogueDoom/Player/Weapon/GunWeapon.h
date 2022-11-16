// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Accessory.h"
#include "Components/SkeletalMeshComponent.h"

#include "GunWeapon.generated.h"

class IAccessoryInterface;

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
class ROGUEDOOM_API UGunWeapon : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGunData Data;
	UPROPERTY()
	TScriptInterface<IAccessoryInterface> Accessory;
	bool ShootAble = true;
	
private:
	FTimerHandle ShootTimerHandle;
	
public:
	virtual void BeginPlay() override
	{
		Super::BeginPlay();
		Accessory = NewObject<ABottomAngledGrip>(NewObject<ATopRedDotScope>(NewObject<AAccessoryDecorator>(NewObject<AAccessory>())));
		UE_LOG(LogTemp, Warning, TEXT("BeginPlay Price: %d"), Accessory->Price());
	}
	virtual void InitSetting() PURE_VIRTUAL(UGunWeapon::InitSetting,);
	virtual void Using(const FTransform Muzzle);
};

UCLASS()
class ROGUEDOOM_API URifleWeapon final : public UGunWeapon
{
	GENERATED_BODY()

public:
	URifleWeapon();
	
	virtual void InitSetting() override;
	virtual void Using(const FTransform Muzzle) override;
};