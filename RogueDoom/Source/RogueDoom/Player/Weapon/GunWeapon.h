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
	UParticleSystem* FireEffect;
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
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MinDamage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxDamage;
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
	virtual FGunData GetData() = 0;
	virtual void Display() = 0;
	virtual void Fire(class UPlayerCharacterAnimInstance& AnimInstance, const FTransform Muzzle, const FVector TraceStartLocation,  const FVector TraceEndLocation) = 0;
	virtual void Reload(UPlayerCharacterAnimInstance& AnimInstance) = 0;
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
	void ChangeAccessory(UAccessoryDecorator* Socket, const TSubclassOf<UAccessoryDecorator> Decorator)const;
};

UCLASS()
class ROGUEDOOM_API UGunWeapon : public USkeletalMeshComponent, public IWeaponInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGunData Data;
	
	bool ShootAble = true;

private:
	FTimerHandle ShootTimerHandle;
	
public:
	virtual FGunData GetData() override {return FGunData{};}
	virtual void Display() override {}
	virtual void Fire(UPlayerCharacterAnimInstance& AnimInstance, const FTransform Muzzle, const FVector TraceStartLocation,  const FVector TraceEndLocation) override;
	virtual void Reload(UPlayerCharacterAnimInstance& AnimInstance) override;
	
	void HitCheck(const FTransform Muzzle, const FVector TraceStartLocation,  const FVector TraceEndLocation)const;
	void SpawnHitEffect(const FHitResult HitResult)const;
	void StopShooting();
};

UCLASS()
class ROGUEDOOM_API URifleWeapon final : public UGunWeapon
{
	GENERATED_BODY()

public:
	
public:	
	URifleWeapon();

	virtual FGunData GetData() override;
	virtual void Display() override;
	virtual void Fire(UPlayerCharacterAnimInstance& AnimInstance, const FTransform Muzzle, const FVector TraceStartLocation,  const FVector TraceEndLocation) override;
	virtual void Reload(UPlayerCharacterAnimInstance& AnimInstance) override;
};

UCLASS()
class ROGUEDOOM_API UPistolWeapon final : public UGunWeapon
{
	GENERATED_BODY()

public:
	
public:	
	UPistolWeapon();

	virtual FGunData GetData() override;
	virtual void Display() override;
	virtual void Fire(UPlayerCharacterAnimInstance& AnimInstance, const FTransform Muzzle, const FVector TraceStartLocation,  const FVector TraceEndLocation) override;
	virtual void Reload(UPlayerCharacterAnimInstance& AnimInstance) override;
};