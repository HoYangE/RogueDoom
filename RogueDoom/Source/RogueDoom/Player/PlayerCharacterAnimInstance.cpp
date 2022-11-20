// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterAnimInstance.h"

#include "PlayerCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance()
{
	IsInAir = false;
	WeaponType = EWeaponType::Rifle;
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if(const auto Pawn = TryGetPawnOwner(); ::IsValid(Pawn))
	{		
		if(const auto Character = Cast<APlayerCharacter>(Pawn); Character)
			IsInAir = Character->GetMovementComponent()->IsFalling();
	}
}
