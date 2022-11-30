// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ROGUEDOOM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* MainCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UPlayerCharacterAnimInstance* AnimInstance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AActor* WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hook, meta = (AllowPrivateAccess = "true"))
	AActor* HookClass;
	
private:

	
public:
	TPair<FVector, FVector> LookAtCenterTarget()const;
	FVector2D FindScreenCenter()const;
	void DeProjectScreenPositionToWorld(const float ScreenX,const float ScreenY,FVector& WorldLocation,FVector& WorldDirection)const;
	void LookAt(const FVector Target)const;
	
private:
	APlayerCharacter();
	void InitMesh()const;
	void InitWeapon();
	void InitCamera();
	void InitSetting();

	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void VelocityTurnAtRate(const bool bZeroVector);
	
	void MoveForward(float Value);
	void MoveRight(float Value);

	void Fire(float Rate);
	void Reload();
	void Rifle();
	void Pistol();
	void ChangeWeapon(const class AWeapon* Weapon)const;

	void Hook();
	void HookPoint();
};
