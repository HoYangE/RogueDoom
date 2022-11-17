// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

#include "Accessory.generated.h"

UINTERFACE()
class UAccessoryInterface : public UInterface
{
	GENERATED_BODY()
};
class IAccessoryInterface
{
	GENERATED_BODY()
public:
	virtual UStaticMesh* GetMesh() = 0;
	virtual FName GetSocketName() = 0;
};

UCLASS()
class ROGUEDOOM_API UAccessoryDecorator : public UStaticMeshComponent, public IAccessoryInterface
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	UStaticMesh* Accessory;
	
public:
	virtual UStaticMesh* GetMesh() override { return Accessory; }
	virtual FName GetSocketName() override { return FName(""); }
};

UCLASS()
class ROGUEDOOM_API UTopRedDotScope final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	UTopRedDotScope()
	{
		if(const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Mesh(TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body57.GUN_PARTS_1____Body57")); SM_Mesh.Succeeded())
			Accessory = SM_Mesh.Object;
	}
	virtual UStaticMesh* GetMesh() override{return Accessory;}
	virtual FName GetSocketName() override{return "Top_RedDotScope_1";}
};
UCLASS()
class ROGUEDOOM_API UTopRedDotScope2 final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	UTopRedDotScope2()
	{
		if(const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Mesh(TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body62.GUN_PARTS_1____Body62")); SM_Mesh.Succeeded())
			Accessory = SM_Mesh.Object;
	}
	virtual UStaticMesh* GetMesh() override{return Accessory;}
	virtual FName GetSocketName() override{return "Top_RedDotScope_2";}
};
UCLASS()
class ROGUEDOOM_API UTopRedDotScope3 final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	UTopRedDotScope3()
	{
		if(const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Mesh(TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body17.GUN_PARTS_1____Body17")); SM_Mesh.Succeeded())
			Accessory = SM_Mesh.Object;
	}
	virtual UStaticMesh* GetMesh() override{return Accessory;}
	virtual FName GetSocketName() override{return "Top_RedDotScope_3";}
};
UCLASS()
class ROGUEDOOM_API UBottomAngledGrip final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	UBottomAngledGrip()
	{
		if(const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Mesh(TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body6.GUN_PARTS_1____Body6")); SM_Mesh.Succeeded())
			Accessory = SM_Mesh.Object;
	}
	virtual UStaticMesh* GetMesh() override{return Accessory;}
	virtual FName GetSocketName() override{return "Bottom_AngledGrip";}
};
UCLASS()
class ROGUEDOOM_API UForwardFlashHider final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	UForwardFlashHider()
	{
		if(const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Mesh(TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body1.GUN_PARTS_1____Body1")); SM_Mesh.Succeeded())
			Accessory = SM_Mesh.Object;
	}
	virtual UStaticMesh* GetMesh() override{return Accessory;}
	virtual FName GetSocketName() override{return "Forward_FlashHider";}
};
UCLASS()
class ROGUEDOOM_API UForwardSilencer final : public UAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	UForwardSilencer()
	{
		if(const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Mesh(TEXT("/Game/StartData/MilitaryWeapSilver/Weapons/Parts/GUN_PARTS_1____Body58_1.GUN_PARTS_1____Body58_1")); SM_Mesh.Succeeded())
			Accessory = SM_Mesh.Object;
	}
	virtual UStaticMesh* GetMesh() override{return Accessory;}
	virtual FName GetSocketName() override{return "Forward_Silencer";}
};