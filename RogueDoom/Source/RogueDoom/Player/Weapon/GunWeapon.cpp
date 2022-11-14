// Fill out your copyright notice in the Description page of Project Settings.


#include "GunWeapon.h"

#include "RogueDoom/GameManager/RogueDoom.h"

#pragma region UGunWeapon
void UGunWeapon::Using(const FTransform Muzzle)
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
}
void URifleWeapon::InitSetting()
{
	Data.Info = "Rifle";
	Data.Transform = FTransform(FRotator(0, 90, 15), FVector(-7, 3, 0), FVector(1, 1, 1));
	Data.DelayTime = 0.5f;
	Data.MaxBullet = 30;
	Data.CurrentBullet = Data.MaxBullet;
}
void URifleWeapon::Using(const FTransform Muzzle)
{
	UGunWeapon::Using(Muzzle);
}
#pragma endregion URifleWeapon