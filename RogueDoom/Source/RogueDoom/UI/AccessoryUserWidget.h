// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AccessoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROGUEDOOM_API UAccessoryUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	
private:
	UPROPERTY()
	class URogueDoomGameInstance* GameInstance;
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

public:
	UFUNCTION(BlueprintCallable)
	void RedDot1ButtonClicked();
	UFUNCTION(BlueprintCallable)
	void RedDot2ButtonClicked();
	UFUNCTION(BlueprintCallable)
	void RedDot3ButtonClicked();

	UFUNCTION(BlueprintCallable)
	void AngledGripButtonClicked();

	UFUNCTION(BlueprintCallable)
	void FlashHiderButtonClicked();
	UFUNCTION(BlueprintCallable)
	void SilencerButtonClicked();
private:
	virtual void NativeConstruct() override;
	
};
