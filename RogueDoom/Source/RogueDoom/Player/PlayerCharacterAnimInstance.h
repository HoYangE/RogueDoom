// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInstance.generated.h"

UENUM(BluePrintType)
enum class EWeaponType :uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Rifle   UMETA(DisplayName = "Rifle"),
	Pistol  UMETA(DisplayName = "Pistol"),
};
UENUM(BluePrintType)
enum class ESpeedType :uint8
{
	Walk = 0 UMETA(DisplayName = "Walk"),
	Run   UMETA(DisplayName = "Run"),
	Sprint  UMETA(DisplayName = "Sprint"),
};
USTRUCT(BlueprintType)
struct FData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EWeaponType WeaponType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	float ForwardInputAxis;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	float RightInputAxis;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	ESpeedType SpeedType;
};

UCLASS()
class ROGUEDOOM_API UPlayerCharacterAnimInstance final : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	FData Data;
	
private:
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bLeftHandIK;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* FireMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ReloadMontage;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* RiflePullOutMontage;
	
	FTimerHandle ReloadTimerHandle;
	FTimerHandle RiflePullOutTimerHandle;
	
public:
	void PlayFireMontage();
	void PlayReloadMontage();
	void PlayRiflePullOutMontage();

	void ChangeSpeedType(const ESpeedType SpeedType);
private:
	UPlayerCharacterAnimInstance();
	
	virtual void NativeUpdateAnimation(const float DeltaSeconds) override;
	void UseLeftHandIK();

};
