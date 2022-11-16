// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/GunWeapon.h"

#pragma region Init
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InitMesh();
	InitCamera();
	InitWeapon();
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
	if(ConstructorHelpers::FClassFinder<UAnimInstance> AI_Player(TEXT("/Game/Animation/UE5/AB_Quinn_Anim.AB_Quinn_Anim_C")); AI_Player.Succeeded())
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
	GunWeapon = CreateDefaultSubobject<URifleWeapon>(TEXT("GunWeapon"));
	GunWeapon->SetupAttachment(GetMesh(),TEXT("RightHandSocket"));	
	
	GunWeapon->InitSetting();
	GunWeapon->SetRelativeLocationAndRotation(GunWeapon->Data.Transform.GetLocation(), GunWeapon->Data.Transform.GetRotation());
}
void APlayerCharacter::InitSetting()
{
	GetCapsuleComponent()->InitCapsuleSize(40.f, 90.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}
#pragma endregion Init

#pragma region Virtual
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GunWeapon->SetSkeletalMesh(GunWeapon->Data.Mesh);

	//GunWeapon->Using(FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f)));
}
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//KeyboardAction
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//MouseAction
	//...
	
	//KeyboardAxis
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerCharacter::MoveRight);

	//MouseAxis
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
}
#pragma endregion Virtual

#pragma region Movement
void APlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * GetWorld()->GetDeltaSeconds());
}
void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * GetWorld()->GetDeltaSeconds());
}
void APlayerCharacter::MoveForward(float Value)
{
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
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
#pragma endregion Movement
