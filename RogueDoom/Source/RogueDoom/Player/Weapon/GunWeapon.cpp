// Fill out your copyright notice in the Description page of Project Settings.


#include "GunWeapon.h"

#include "Accessory.h"
#include "CollisionDebugDrawingPublic.h"
#include "Kismet/KismetMathLibrary.h"
#include "RogueDoom/GameManager/RogueDoom.h"
#include "RogueDoom/GameManager/RogueDoomGameInstance.h"
#include "RogueDoom/Player/PlayerCharacter.h"
#include "RogueDoom/Player/PlayerCharacterAnimInstance.h"

#pragma region AWeapon
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GunWeapon = CreateDefaultSubobject<URifleWeapon>(TEXT("GunWeaponMesh"));
	GunWeapon->Data = URifleWeapon::StaticClass()->GetDefaultObject<UGunWeapon>()->GetData();
	SetRootComponent(GunWeapon);

	GunWeapon->SetSkeletalMesh(GunWeapon->Data.Mesh);

	ScopeAccessory = CreateDefaultSubobject<UAccessoryDecorator>(TEXT("ScopeAccessory"));
	ScopeAccessory->SetCollisionProfileName(TEXT("NoCollision"));	
	ChangeAccessory(ScopeAccessory, UTopRedDotScope1::StaticClass());
	
	LeftHandAccessory = CreateDefaultSubobject<UAccessoryDecorator>(TEXT("LeftHandAccessory"));
	LeftHandAccessory->SetCollisionProfileName(TEXT("NoCollision"));
	ChangeAccessory(LeftHandAccessory, UBottomAngledGrip::StaticClass());

	MuzzleAccessory = CreateDefaultSubobject<UAccessoryDecorator>(TEXT("MuzzleAccessory"));
	MuzzleAccessory->SetCollisionProfileName(TEXT("NoCollision"));
	ChangeAccessory(MuzzleAccessory, UForwardSilencer::StaticClass());
}
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}
void AWeapon::ChangeAccessory(UAccessoryDecorator* Socket, const TSubclassOf<UAccessoryDecorator> Decorator)const
{
	if(Decorator == nullptr)
	{
		Socket->SetStaticMesh(nullptr);
		Socket->Data = FAccessoryData();
		return;
	}	
	if(const auto Temp = Decorator->GetDefaultObject<UAccessoryDecorator>()->GetAccessoryData(); GunWeapon->DoesSocketExist(Temp.SocketName))
	{
		if(Socket->Data.SocketName == Temp.SocketName)
		{
			Socket->SetStaticMesh(nullptr);
			Socket->Data = FAccessoryData();
			return;
		}
		Socket->Data = Temp;
		Socket->AttachToComponent(GunWeapon, FAttachmentTransformRules::KeepRelativeTransform, Temp.SocketName);
		Socket->SetStaticMesh(Temp.Mesh);
	}
}
#pragma endregion AWeapon


#pragma region UGunWeapon
void UGunWeapon::Fire(UPlayerCharacterAnimInstance& AnimInstance, const FTransform Muzzle, const FVector TraceStartLocation,  const FVector TraceEndLocation)
{
	if(ShootAble && Data.CurrentBullet > 0)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Data.FireEffect, Muzzle);

		AnimInstance.PlayFireMontage();
		HitEffect(Muzzle, TraceStartLocation, TraceEndLocation);
		
		Data.CurrentBullet--;
		
		ShootAble = false;
		GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, [&]{ShootAble = true;}, Data.DelayTime, false);
	}
	else if(Data.CurrentBullet <= 0)
	{
		Reload(AnimInstance);
	}
}
void UGunWeapon::Reload(UPlayerCharacterAnimInstance& AnimInstance)
{
	StopShooting();
	AnimInstance.PlayReloadMontage();
	Data.CurrentBullet = Data.MaxBullet;
}
void UGunWeapon::HitEffect(const FTransform Muzzle, const FVector TraceStartLocation,  const FVector TraceEndLocation)const
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStartLocation, TraceEndLocation, ECC_Visibility);
	if(HitResult.bBlockingHit)
	{
		FHitResult HitResult2;
		GetWorld()->LineTraceSingleByChannel(HitResult2, Muzzle.GetLocation(), HitResult.ImpactPoint + HitResult.ImpactNormal*-1.1f, ECC_Visibility);
		if(HitResult2.bBlockingHit)
		{
			auto HitEffect = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/FX/P_Impact_Metal_Medium_01.P_Impact_Metal_Medium_01"));
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitResult2.ImpactPoint);
		}
	}
}
void UGunWeapon::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootTimerHandle);
}
#pragma endregion UGunWeapon


#pragma region URifleWeapon
URifleWeapon::URifleWeapon()
{

}
FGunData URifleWeapon::GetData()
{
	Data.Mesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Assault_Rifle_A.Assault_Rifle_A"));
	Data.FireEffect = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/FX/P_AssaultRifle_MuzzleFlash.P_AssaultRifle_MuzzleFlash"));
	Data.Info = "Rifle";
	Data.Transform = FTransform(FRotator(0, 90, 15), FVector(-7, 3, 0), FVector(1, 1, 1));
	Data.DelayTime = 0.15f;
	Data.MaxBullet = 30;
	Data.CurrentBullet = Data.MaxBullet;
	
	return Data;
}
void URifleWeapon::Display()
{

}
void URifleWeapon::Fire(UPlayerCharacterAnimInstance& AnimInstance, const FTransform Muzzle, const FVector TraceStartLocation,  const FVector TraceEndLocation)
{
	UGunWeapon::Fire(AnimInstance, Muzzle, TraceStartLocation, TraceEndLocation);
}
void URifleWeapon::Reload(UPlayerCharacterAnimInstance& AnimInstance)
{
	UGunWeapon::Reload(AnimInstance);
}

#pragma endregion URifleWeapon


#pragma region UPistol
UPistolWeapon::UPistolWeapon()
{

}
FGunData UPistolWeapon::GetData()
{
	Data.Mesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Pistols_A.Pistols_A"));
	Data.FireEffect = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/FX/P_AssaultRifle_MuzzleFlash.P_AssaultRifle_MuzzleFlash"));
	Data.Info = "Pistol";
	Data.Transform = FTransform(FRotator(0, 90, 15), FVector(-7, 3, 0), FVector(1, 1, 1));
	Data.DelayTime = 0.5f;
	Data.MaxBullet = 15;
	Data.CurrentBullet = Data.MaxBullet;
	
	return Data;
}
void UPistolWeapon::Display()
{
	
}
void UPistolWeapon::Fire(UPlayerCharacterAnimInstance& AnimInstance, const FTransform Muzzle, const FVector TraceStartLocation,  const FVector TraceEndLocation)
{
	UGunWeapon::Fire(AnimInstance, Muzzle, TraceStartLocation, TraceEndLocation);
}
void UPistolWeapon::Reload(UPlayerCharacterAnimInstance& AnimInstance)
{
	UGunWeapon::Reload(AnimInstance);
}
#pragma endregion UPistol