// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterAnimInstance.h"

#include "PlayerCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "RogueDoom/GameManager/RogueDoom.h"
#include "Weapon/GunWeapon.h"

UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance()
{
	Data.IsInAir = false;
	Data.WeaponType = EWeaponType::Rifle;
	Data.ForwardInputAxis = 0.0f;
	Data.RightInputAxis = 0.0f;
	Data.SpeedType = ESpeedType::Walk;

	bLeftHandIK = true;
	
	if(const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Fire(TEXT("/Game/Animation/UE5/Rifle/Etc/Rifle_Finger_Montage.Rifle_Finger_Montage")); AM_Fire.Succeeded())
		FireMontage = AM_Fire.Object;
	if(const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Reload(TEXT("/Game/Animation/UE5/Rifle/Reload/Rifle_IdleReload_Montage.Rifle_IdleReload_Montage")); AM_Reload.Succeeded())
		ReloadMontage = AM_Reload.Object;
	if(const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RiflePullOut(TEXT("/Game/Animation/UE5/Rifle/Etc/Rifle_PullOut_Montage.Rifle_PullOut_Montage")); AM_RiflePullOut.Succeeded())
		RiflePullOutMontage = AM_RiflePullOut.Object;
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if(const auto Pawn = TryGetPawnOwner(); ::IsValid(Pawn))
	{
		if(PlayerCharacter = Cast<APlayerCharacter>(Pawn); PlayerCharacter)
			Data.IsInAir = PlayerCharacter->GetMovementComponent()->IsFalling();
	}
}

void UPlayerCharacterAnimInstance::PlayFireMontage()
{
	if(FireMontage)
		Montage_Play(FireMontage, 1.0f);
}
void UPlayerCharacterAnimInstance::PlayReloadMontage()
{
	bLeftHandIK = false;
	if(const auto Weapon = Cast<AWeapon>(PlayerCharacter->WeaponClass);Weapon)
		if(const auto GunWeapon = Cast<UGunWeapon>(Weapon->GunWeapon);GunWeapon)
			GunWeapon->ShootAble = false;
	const float Time = Montage_Play(ReloadMontage);
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &UPlayerCharacterAnimInstance::UseLeftHandIK, Time);
}
void UPlayerCharacterAnimInstance::PlayRiflePullOutMontage()
{
	bLeftHandIK = false;
	if(const auto Weapon = Cast<AWeapon>(PlayerCharacter->WeaponClass);Weapon)
		if(const auto GunWeapon = Cast<UGunWeapon>(Weapon->GunWeapon);GunWeapon)
			GunWeapon->ShootAble = false;
	const float Time = Montage_Play(RiflePullOutMontage);
	GetWorld()->GetTimerManager().SetTimer(RiflePullOutTimerHandle, this, &UPlayerCharacterAnimInstance::UseLeftHandIK, Time);
}
void UPlayerCharacterAnimInstance::UseLeftHandIK()
{
	bLeftHandIK = true;

	if(const auto Weapon = Cast<AWeapon>(PlayerCharacter->WeaponClass);Weapon)
		if(const auto GunWeapon = Cast<UGunWeapon>(Weapon->GunWeapon);GunWeapon)
			GunWeapon->ShootAble = true;
}
