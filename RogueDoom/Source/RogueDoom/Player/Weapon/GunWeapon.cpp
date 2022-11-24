// Fill out your copyright notice in the Description page of Project Settings.


#include "GunWeapon.h"

#include "Accessory.h"
#include "RogueDoom/GameManager/RogueDoom.h"

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

}
FGunData URifleWeapon::GetData()
{
	Data.Mesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Assault_Rifle_A.Assault_Rifle_A"));
	Data.Info = "Rifle";
	Data.Transform = FTransform(FRotator(0, 90, 15), FVector(-7, 3, 0), FVector(1, 1, 1));
	Data.DelayTime = 0.5f;
	Data.MaxBullet = 30;
	Data.CurrentBullet = Data.MaxBullet;
	
	return Data;
}
void URifleWeapon::Display()
{

}
void URifleWeapon::Fire(const FTransform Muzzle)
{
	UGunWeapon::Fire(Muzzle);	
}
#pragma endregion URifleWeapon


#pragma region UPistol
UPistolWeapon::UPistolWeapon()
{

}
FGunData UPistolWeapon::GetData()
{
	Data.Mesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Pistols_A.Pistols_A"));
	Data.Info = "Pistol";
	Data.Transform = FTransform(FRotator(0, 90, 15), FVector(-7, 3, 0), FVector(1, 1, 1));
	Data.DelayTime = 0.75f;
	Data.MaxBullet = 15;
	Data.CurrentBullet = Data.MaxBullet;
	
	return Data;
}
void UPistolWeapon::Display()
{
	
}
void UPistolWeapon::Fire(const FTransform Muzzle)
{
	UGunWeapon::Fire(Muzzle);	
}
#pragma endregion UPistol