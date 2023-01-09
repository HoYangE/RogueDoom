// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineMeshComponent.h"
#include "GrapplingHook.generated.h"

/**
 * 
 */
UCLASS()
class ROGUEDOOM_API AGrapplingHook final : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	USplineMeshComponent* SplineMesh;
	
	bool bIsHooking;
	
private:
	UPROPERTY()
	class URogueDoomGameInstance* GameInstance;
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	UCurveFloat* HookMoveCurve;
	UPROPERTY()
	UCurveFloat* HookPlayerMoveCurve;

	FTimerHandle HookMoveTimerHandle;
	FTimerHandle HookPlayerMoveTimerHandle;

	float HookMoveCurveFloatValue;
	float HookPlayerMoveCurveFloatValue;
	
	FVector HookStartLocation;
	FVector HookEndLocation;
	

public:	
	void Hook();
	void HookMove();
	void HookMoveEnd();
	void HookPlayerMove();
	void HookPlayerMoveEnd();

	void SetPoints(const FVector StartLocation, const FVector EndLocation);
private:
	AGrapplingHook();
	void SplineInit();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
