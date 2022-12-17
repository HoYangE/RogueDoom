// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "GrapplingHook.h"
#include "PlayerCharacterAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "RogueDoom/GameManager/RogueDoom.h"
#include "RogueDoom/GameManager/RogueDoomGameInstance.h"
#include "RogueDoom/LevelManager/LevelRoomSearchTree.h"
#include "Weapon/GunWeapon.h"


#pragma region Init
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InitMesh();
	InitCamera();
	InitSetting();
}
void APlayerCharacter::InitMesh()const
{
	// C++ 17 init statement for if
	if(const ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Player(TEXT("/Game/StartData/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn")); SK_Player.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Player.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	if(ConstructorHelpers::FClassFinder<UAnimInstance> AI_Player(TEXT("/Game/Animation/UE5/AnimBP/AB_Quinn_Anim.AB_Quinn_Anim_C")); AI_Player.Succeeded())
	{
		GetMesh()->SetAnimClass(AI_Player.Class);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,-92.0f), FRotator(0.0f, -90.0f, 0.0f));

}
void APlayerCharacter::InitCamera()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SocketOffset = FVector(0.0f, 40.0f, 30.0f);
	SpringArm->bUsePawnControlRotation = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	MainCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	MainCamera->bUsePawnControlRotation = false;
	MainCamera->FieldOfView = 100.0f;
}
void APlayerCharacter::InitWeapon()
{
	const auto SocketTransform = GetMesh()->GetSocketTransform(TEXT("RightHandSocket"));
	WeaponClass = GetWorld()->SpawnActor(AWeapon::StaticClass(),&SocketTransform);
	WeaponClass->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,TEXT("RightHandSocket"));
}
void APlayerCharacter::InitSetting()
{
	GetCapsuleComponent()->InitCapsuleSize(40.f, 90.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.0f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}
void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
}
#pragma endregion Init


#pragma region Virtual
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(const auto GameInstance = Cast<URogueDoomGameInstance>(GetGameInstance()); GameInstance)
		GameInstance->SetPlayerCharacter(this);
	
	InitWeapon();
}
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	HookPoint();
}
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//KeyboardAction
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);
	PlayerInputComponent->BindAction("Hook", IE_Pressed, this, &APlayerCharacter::Hook);
	PlayerInputComponent->BindAction("ChangeSpeedEnum", IE_Pressed, this, &APlayerCharacter::ChangeSpeedEnum);

	PlayerInputComponent->BindAction("Rifle", IE_Pressed, this, &APlayerCharacter::Rifle);
	PlayerInputComponent->BindAction("Pistol", IE_Pressed, this, &APlayerCharacter::Pistol);
	//MouseAction
	//...
	
	//KeyboardAxis
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Fire", this, &APlayerCharacter::Fire);

	//MouseAxis
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APlayerCharacter::LookUpAtRate);
}
#pragma endregion Virtual


#pragma region Movement
void APlayerCharacter::TurnAtRate(float Rate)
{
	VelocityTurnAtRate(GetCharacterMovement()->Velocity == FVector::ZeroVector);	
	AddControllerYawInput(Rate * GetWorld()->GetDeltaSeconds() * 100.0f);
}
void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * GetWorld()->GetDeltaSeconds() * 100.0f);
}
void APlayerCharacter::VelocityTurnAtRate(const bool bZeroVector)
{
	GetCharacterMovement()->bOrientRotationToMovement = bZeroVector;
	bUseControllerRotationYaw = !bZeroVector;
}

void APlayerCharacter::MoveForward(float Value)
{
	AnimInstance->Data.ForwardInputAxis = Value;
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
void APlayerCharacter::MoveRight(float Value)
{
	AnimInstance->Data.RightInputAxis = Value;
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
void APlayerCharacter::ChangeSpeedEnum()
{
	if(AnimInstance->Data.SpeedType == ESpeedType::Walk)
		AnimInstance->ChangeSpeedType(ESpeedType::Run);
	else
		AnimInstance->ChangeSpeedType(ESpeedType::Sprint);
}

#pragma endregion Movement


#pragma region Weapon
void APlayerCharacter::Fire(float Rate)
{
	if(const auto Weapon = Cast<AWeapon>(WeaponClass); Weapon && Rate > 0.0f)
	{
		if(Weapon->GunWeapon->DoesSocketExist(TEXT("MuzzleSocket")))
		{
			const auto Trace = LookAtCenterTarget();
			FTransform MuzzleTransform = Weapon->GunWeapon->GetSocketTransform(TEXT("MuzzleSocket")) + Weapon->MuzzleAccessory->GetAccessoryData().Transform;
			MuzzleTransform.SetRotation(GetActorRotation().Quaternion());

			if(AnimInstance->Data.SpeedType == ESpeedType::Sprint)
				AnimInstance->ChangeSpeedType(ESpeedType::Run);
			
			Weapon->GunWeapon->Fire(*AnimInstance,MuzzleTransform, Trace.Get<0>(), Trace.Get<1>());
		}
	}
}
void APlayerCharacter::Reload()
{
	if(const auto Weapon = Cast<AWeapon>(WeaponClass); Weapon)
	{
		Weapon->GunWeapon->Reload(*AnimInstance);
	}
}
void APlayerCharacter::Rifle()
{
	const auto Data = URifleWeapon::StaticClass()->GetDefaultObject<UGunWeapon>()->GetData();
	if(const auto Weapon = Cast<AWeapon>(WeaponClass); Weapon && Weapon->GunWeapon->Data.Mesh != Data.Mesh)
	{
		AnimInstance->Data.WeaponType = EWeaponType::Rifle;
		Weapon->GunWeapon->Data = Data;
		AnimInstance->PlayRiflePullOutMontage();
		ChangeWeapon(Weapon);
	}
}
void APlayerCharacter::Pistol()
{
	const auto Data = UPistolWeapon::StaticClass()->GetDefaultObject<UGunWeapon>()->GetData();
	if(const auto Weapon = Cast<AWeapon>(WeaponClass); Weapon && Weapon->GunWeapon->Data.Mesh != Data.Mesh)
	{
		AnimInstance->Data.WeaponType = EWeaponType::Pistol;
		Weapon->GunWeapon->Data = Data;
		AnimInstance->PlayRiflePullOutMontage();
		ChangeWeapon(Weapon);
	}
}
void APlayerCharacter::ChangeWeapon(const AWeapon* Weapon)const
{
	Weapon->ChangeAccessory(Weapon->ScopeAccessory, nullptr);
	Weapon->ChangeAccessory(Weapon->LeftHandAccessory, nullptr);
	Weapon->ChangeAccessory(Weapon->MuzzleAccessory, nullptr);
	Weapon->GunWeapon->SetSkeletalMesh(Weapon->GunWeapon->Data.Mesh);
	if(const auto GunWeapon = Cast<UGunWeapon>(Weapon->GunWeapon);GunWeapon)
		GunWeapon->StopShooting();
}
#pragma endregion Weapon


#pragma region OtherInput
void APlayerCharacter::Hook()
{
	if(!HookClass)
	{
		HookClass = GetWorld()->SpawnActor(AGrapplingHook::StaticClass());
		HookClass->SetActorTransform(GetActorTransform());

		if(const auto Hook = Cast<AGrapplingHook>(HookClass); Hook)
		{
			Hook->Hook();
			if(!Hook->bIsHooking)
			{
				HookClass->Destroy();
				HookClass = nullptr;
			}
		}
	}
}
#pragma endregion OtherInput


#pragma region Function
#pragma region LookAt
TPair<FVector, FVector> APlayerCharacter::LookAtCenterTarget() const
{
	const FVector2D ScreenCenter = FindScreenCenter();

	FVector TraceStartLocation;
	FVector CameraDirection;
	DeProjectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, TraceStartLocation, CameraDirection);
	const FVector TraceEndLocation = TraceStartLocation + CameraDirection * 1500.0f;

	LookAt(TraceEndLocation);

	return TPair<FVector, FVector>(TraceStartLocation, TraceEndLocation);
}
FVector2D APlayerCharacter::FindScreenCenter() const
{
	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	int32 ViewportSizeX, ViewportSizeY;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	return FVector2D(ViewportSizeX * 0.5f, ViewportSizeY * 0.5f);
}
void APlayerCharacter::DeProjectScreenPositionToWorld(const float ScreenX, const float ScreenY, FVector& WorldLocation, FVector& WorldDirection)const
{
	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->DeprojectScreenPositionToWorld(ScreenX, ScreenY, WorldLocation, WorldDirection);
}
void APlayerCharacter::LookAt(const FVector Target)const
{
	const auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	const float Yaw = UKismetMathLibrary::FindLookAtRotation(Player->GetActorLocation(), Target).Yaw;
	Player->SetActorRotation(FRotator(0.0f, Yaw, 0.0f));
}
#pragma endregion LookAt


#pragma region Hook
void APlayerCharacter::HookPoint()
{
	const FVector2D ScreenCenter = FindScreenCenter();

	FVector TraceStartLocation;
	FVector CameraDirection;
	DeProjectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, TraceStartLocation, CameraDirection);
	const FVector TraceEndLocation = TraceStartLocation + CameraDirection * 1500.0f;
	
	TraceStartLocation = TraceStartLocation + CameraDirection * 200.0f;	

	FHitResult HitResult;
	GetWorld()->SweepSingleByChannel(HitResult,TraceStartLocation,TraceEndLocation,FQuat::Identity,
		ECollisionChannel::ECC_Visibility,FCollisionShape::MakeCapsule(30,0));
	if(HitResult.bBlockingHit)
		DrawDebugPoint(GetWorld(),HitResult.ImpactPoint,30.0f,FColor::Purple,false,0.1f);
}
#pragma endregion Hook



#pragma endregion 