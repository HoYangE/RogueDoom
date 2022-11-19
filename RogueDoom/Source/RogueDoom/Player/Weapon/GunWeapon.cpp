// Fill out your copyright notice in the Description page of Project Settings.


#include "GunWeapon.h"

#include "Accessory.h"
#include "RogueDoom/GameManager/RogueDoom.h"

#pragma region AWeapon
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GunWeapon = CreateDefaultSubobject<URifleWeapon>(TEXT("GunWeaponMesh"));
	SetRootComponent(GunWeapon);

	GunWeapon->SetSkeletalMesh(GunWeapon->Data.Mesh);

	ScopeAccessory = CreateDefaultSubobject<UAccessoryDecorator>(TEXT("ScopeAccessory"));
	ScopeAccessory->SetCollisionProfileName(TEXT("NoCollision"));	
	ChangeAccessory(ScopeAccessory, UTopRedDotScope::StaticClass());
	
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
	Socket->SetupAttachment(GunWeapon, Decorator->GetDefaultObject<UAccessoryDecorator>()->GetSocketName());
	Socket->SetStaticMesh(Decorator->GetDefaultObject<UAccessoryDecorator>()->GetMesh());
}
#pragma endregion AWeapon


#pragma region UGunWeapon
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
#pragma endregion UGunWeapon


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