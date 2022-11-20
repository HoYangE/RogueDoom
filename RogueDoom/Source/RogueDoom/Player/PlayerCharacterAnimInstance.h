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

UCLASS()
class ROGUEDOOM_API UPlayerCharacterAnimInstance final : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EWeaponType WeaponType;
private:

	
public:

	
private:
	UPlayerCharacterAnimInstance();
	
	virtual void NativeUpdateAnimation(const float DeltaSeconds) override;

	
};
