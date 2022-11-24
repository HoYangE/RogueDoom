// Fill out your copyright notice in the Description page of Project Settings.


#include "Accessory.h"

FAccessoryData UTopRedDotScope1::GetAccessoryData()
{
	Data.Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body57.GUN_PARTS_1____Body57"));
	Data.Info = "";
	Data.Transform = FTransform(FRotator(0,0,0),FVector(0,0,0),FVector(1,1,1));
	Data.SocketName = "Top_RedDotScope_1";
	
	return Data;
}

FAccessoryData UTopRedDotScope2::GetAccessoryData()
{
	Data.Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body62.GUN_PARTS_1____Body62"));
	Data.Info = "";
	Data.Transform = FTransform(FRotator(0,0,0),FVector(0,0,0),FVector(1,1,1));
	Data.SocketName = "Top_RedDotScope_2";
	return Data;
}

FAccessoryData UTopRedDotScope3::GetAccessoryData()
{
	Data.Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body17.GUN_PARTS_1____Body17"));
	Data.Info = "";
	Data.Transform = FTransform(FRotator(0,0,0),FVector(0,0,0),FVector(1,1,1));
	Data.SocketName = "Top_RedDotScope_3";
	return Data;
}

FAccessoryData UBottomAngledGrip::GetAccessoryData()
{
	Data.Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body6.GUN_PARTS_1____Body6"));
	Data.Info = "";
	Data.Transform = FTransform(FRotator(0,0,0),FVector(0,0,0),FVector(1,1,1));
	Data.SocketName = "Bottom_AngledGrip";
	return Data;
}

FAccessoryData UForwardFlashHider::GetAccessoryData()
{
	Data.Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body1.GUN_PARTS_1____Body1"));
	Data.Info = "";
	Data.Transform = FTransform(FRotator(0,0,0),FVector(8,0,0),FVector(1,1,1));
	Data.SocketName = "Forward_FlashHider";
	return Data;
}

FAccessoryData UForwardSilencer::GetAccessoryData()
{
	Data.Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body58_1.GUN_PARTS_1____Body58_1"));
	Data.Info = "";
	Data.Transform = FTransform(FRotator(0,0,0),FVector(7,0,0),FVector(1,1,1));
	Data.SocketName = "Forward_Silencer";
	return Data;
}
