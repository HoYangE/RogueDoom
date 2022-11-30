// Fill out your copyright notice in the Description page of Project Settings.


#include "AccessoryUserWidget.h"
#include "../GameManager/RogueDoomGameInstance.h"
#include "../GameManager/RogueDoom.h"
#include "RogueDoom/Player/PlayerCharacter.h"
#include "RogueDoom/Player/Weapon/GunWeapon.h"

void UAccessoryUserWidget::NativeConstruct()
{
	GameInstance = Cast<URogueDoomGameInstance>(GetGameInstance());
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}


void UAccessoryUserWidget::RedDot1ButtonClicked()
{
	if(const auto Weapon = Cast<AWeapon>(PlayerCharacter->WeaponClass); Weapon)
		Weapon->ChangeAccessory(Weapon->ScopeAccessory, UTopRedDotScope1::StaticClass());
}
void UAccessoryUserWidget::RedDot2ButtonClicked()
{
	if(const auto Weapon = Cast<AWeapon>(PlayerCharacter->WeaponClass); Weapon)
		Weapon->ChangeAccessory(Weapon->ScopeAccessory, UTopRedDotScope2::StaticClass());
}
void UAccessoryUserWidget::RedDot3ButtonClicked()
{
	if(const auto Weapon = Cast<AWeapon>(PlayerCharacter->WeaponClass); Weapon)
		Weapon->ChangeAccessory(Weapon->ScopeAccessory, UTopRedDotScope3::StaticClass());
}

void UAccessoryUserWidget::AngledGripButtonClicked()
{
	if(const auto Weapon = Cast<AWeapon>(PlayerCharacter->WeaponClass); Weapon)
		Weapon->ChangeAccessory(Weapon->LeftHandAccessory, UBottomAngledGrip::StaticClass());
}

void UAccessoryUserWidget::FlashHiderButtonClicked()
{
	if(const auto Weapon = Cast<AWeapon>(PlayerCharacter->WeaponClass); Weapon)
		Weapon->ChangeAccessory(Weapon->MuzzleAccessory, UForwardFlashHider::StaticClass());
}
void UAccessoryUserWidget::SilencerButtonClicked()
{
	if(const auto Weapon = Cast<AWeapon>(PlayerCharacter->WeaponClass); Weapon)
		Weapon->ChangeAccessory(Weapon->MuzzleAccessory, UForwardSilencer::StaticClass());
}