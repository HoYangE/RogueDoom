// Fill out your copyright notice in the Description page of Project Settings.


#include "GunWeapon.h"

#include "Accessory.h"
#include "RogueDoom/GameManager/RogueDoom.h"
#include "RogueDoom/Player/PlayerCharacter.h"

#pragma region UGunWeapon
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	GunWeapon = CreateDefaultSubobject<URifleWeapon>(TEXT("GunWeaponMesh"));
	GunWeapon->SetupAttachment(RootComponent);

	GunWeapon->SetSkeletalMesh(GunWeapon->Data.Mesh);

	ScopeAccessory = CreateDefaultSubobject<UTopRedDotScope>(TEXT("ScopeAccessory"));
	ScopeAccessory->SetupAttachment(GunWeapon, ScopeAccessory->GetSocketName());
	ScopeAccessory->SetStaticMesh(ScopeAccessory->GetMesh());
	ScopeAccessory->SetCollisionProfileName(TEXT("NoCollision"));
	
	LeftHandAccessory = CreateDefaultSubobject<UBottomAngledGrip>(TEXT("LeftHandAccessory"));
	LeftHandAccessory->SetupAttachment(GunWeapon, LeftHandAccessory->GetSocketName());
	LeftHandAccessory->SetStaticMesh(LeftHandAccessory->GetMesh());
	LeftHandAccessory->SetCollisionProfileName(TEXT("NoCollision"));

	MuzzleAccessory = CreateDefaultSubobject<UForwardSilencer>(TEXT("MuzzleAccessory"));
	MuzzleAccessory->SetupAttachment(GunWeapon, MuzzleAccessory->GetSocketName());
	MuzzleAccessory->SetStaticMesh(MuzzleAccessory->GetMesh());
	MuzzleAccessory->SetCollisionProfileName(TEXT("NoCollision"));

}
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}
#pragma endregion UGunWeapon

void UGunWeapon::Fire(const FTransform Muzzle)
{
	if(ShootAble)
	{
		//bullet make and transform, effect setting
		//...

		Data.CurrentBullet--;
		
		ShootAble = false;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, [&]{ShootAble = true;}, Data.DelayTime, false);
	}
}

#pragma region URifleWeapon
URifleWeapon::URifleWeapon()
{
	if(const ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_GunBody(TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Assault_Rifle_A.Assault_Rifle_A")); SM_GunBody.Succeeded())
	{
		Data.Mesh = SM_GunBody.Object;
	}

	Data.Info = "Rifle";
	Data.Transform = FTransform(FRotator(0, 90, 15), FVector(-7, 3, 0), FVector(1, 1, 1));
	Data.DelayTime = 0.5f;
	Data.MaxBullet = 30;
	Data.CurrentBullet = Data.MaxBullet;
}
void URifleWeapon::InitSetting()
{
	UGunWeapon::InitSetting();
}
void URifleWeapon::Fire(const FTransform Muzzle)
{
	UGunWeapon::Fire(Muzzle);	
}
#pragma endregion URifleWeapon