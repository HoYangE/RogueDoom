// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "UObject/Interface.h"

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
	virtual int Price() = 0;
};

UCLASS()
class ROGUEDOOM_API AAccessory : public AActor, public IAccessoryInterface
{
	GENERATED_BODY()
public:
	virtual int Price() override{return 500;}
};

UCLASS()
class ROGUEDOOM_API AAccessoryDecorator : public AActor, public IAccessoryInterface
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TScriptInterface<IAccessoryInterface> Accessory;
	
public:
	AAccessoryDecorator()=default;//{Accessory = NewObject<AAccessory>();}
	// explicit: 원하지 않는 형변환 제한하는 키워드
	explicit AAccessoryDecorator(const TScriptInterface<IAccessoryInterface> Accessory):Accessory(Accessory){}
	virtual int Price() override{if(Accessory) return Accessory->Price(); return 0;}
};

UCLASS()
class ROGUEDOOM_API ATopRedDotScope final : public AAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	ATopRedDotScope() = default;
	explicit ATopRedDotScope(const TScriptInterface<IAccessoryInterface> Accessory):AAccessoryDecorator::AAccessoryDecorator(Accessory){}
	virtual int Price() override{return AAccessoryDecorator::Price() + 100;}
};
UCLASS()
class ROGUEDOOM_API ATopRedDotScope2 final : public AAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	ATopRedDotScope2() = default;
	explicit ATopRedDotScope2(const TScriptInterface<IAccessoryInterface> Accessory):AAccessoryDecorator::AAccessoryDecorator(Accessory){}
	virtual int Price() override{return AAccessoryDecorator::Price() + 130;}
};
UCLASS()
class ROGUEDOOM_API ATopRedDotScope3 final : public AAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	ATopRedDotScope3() = default;
	explicit ATopRedDotScope3(const TScriptInterface<IAccessoryInterface> Accessory):AAccessoryDecorator::AAccessoryDecorator(Accessory){}
	virtual int Price() override{return AAccessoryDecorator::Price() + 315;}
};
UCLASS()
class ROGUEDOOM_API ABottomAngledGrip final : public AAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	ABottomAngledGrip() = default;
	explicit ABottomAngledGrip(const TScriptInterface<IAccessoryInterface> Accessory):AAccessoryDecorator::AAccessoryDecorator(Accessory){}
	virtual int Price() override{return AAccessoryDecorator::Price() + 250;}
};
UCLASS()
class ROGUEDOOM_API AForwardFlashHider final : public AAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	AForwardFlashHider() = default;
	explicit AForwardFlashHider(const TScriptInterface<IAccessoryInterface> Accessory):AAccessoryDecorator::AAccessoryDecorator(Accessory){}
	virtual int Price() override{return AAccessoryDecorator::Price() + 305;}
};
UCLASS()
class ROGUEDOOM_API AForwardSilencer final : public AAccessoryDecorator
{
	GENERATED_BODY()
	
public:
	AForwardSilencer() = default;
	explicit AForwardSilencer(const TScriptInterface<IAccessoryInterface> Accessory):AAccessoryDecorator::AAccessoryDecorator(Accessory){}
	virtual int Price() override{return AAccessoryDecorator::Price() + 100;}
};