// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterAnimInstance.h"

#include "PlayerCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "RogueDoom/GameManager/RogueDoom.h"

UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance()
{
	Data.IsInAir = false;
	Data.WeaponType = EWeaponType::Rifle;
	Data.ForwardInputAxis = 0.0f;
	Data.RightInputAxis = 0.0f;
	Data.SpeedType = ESpeedType::Walk;
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if(const auto Pawn = TryGetPawnOwner(); ::IsValid(Pawn))
	{
		if(const auto Character = Cast<APlayerCharacter>(Pawn); Character)
			Data.IsInAir = Character->GetMovementComponent()->IsFalling();
	}
}
