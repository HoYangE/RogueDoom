// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapplingHook.h"

#include "PlayerCharacter.h"
#include "../GameManager/RogueDoomGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/MaterialInstanceConstant.h"
#include "RogueDoom/GameManager/RogueDoom.h"


#pragma region Init
AGrapplingHook::AGrapplingHook()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SplineInit();

	if(const ConstructorHelpers::FObjectFinder<UCurveFloat> HookMoveCurveFloat(TEXT("/Game/DataSet/Curves/HookMove.HookMove")); HookMoveCurveFloat.Succeeded())
		HookMoveCurve = HookMoveCurveFloat.Object;
	if(const ConstructorHelpers::FObjectFinder<UCurveFloat> HookPlayerMoveCurveFloat(TEXT("/Game/DataSet/Curves/HookPlayerMove.HookPlayerMove")); HookPlayerMoveCurveFloat.Succeeded())
		HookPlayerMoveCurve = HookPlayerMoveCurveFloat.Object;
	
	HookMoveCurveFloatValue = 0.0f;
	HookPlayerMoveCurveFloatValue = 0.0f;
	bIsHooking = false;
}
void AGrapplingHook::SplineInit()
{
	SplineMesh = CreateDefaultSubobject<USplineMeshComponent>(TEXT("SplineMesh"));
	RootComponent = SplineMesh;
	
	if(const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Cylinder(TEXT("/Engine/EngineMeshes/Cylinder.Cylinder")); SM_Cylinder.Succeeded())
		SplineMesh->SetStaticMesh(SM_Cylinder.Object);
	if(const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_BaseGray(TEXT("/Engine/TemplateResources/MI_Template_BaseGray_Metal.MI_Template_BaseGray_Metal")); MI_BaseGray.Succeeded())
		SplineMesh->SetMaterial(0,MI_BaseGray.Object);
	SplineMesh->SetSplineUpDir(FVector(0,1,0));
	SplineMesh->SetForwardAxis(ESplineMeshAxis::Z);
	SplineMesh->SetStartScale(FVector2D(0.05f,0.05f));
	SplineMesh->SetEndScale(FVector2D(0.05f,0.05f));

	SplineMesh->SetMobility(EComponentMobility::Movable);
	SplineMesh->SetCollisionProfileName(FName("NoCollision"));
}
#pragma endregion Init


#pragma region Virtual
void AGrapplingHook::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<URogueDoomGameInstance>(GetGameInstance());
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}
void AGrapplingHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SplineMesh->SetStartPosition(UKismetMathLibrary::InverseTransformLocation(GetActorTransform(), PlayerCharacter->GetActorLocation()));
}
#pragma endregion Virtual


#pragma region Hook
void AGrapplingHook::Hook()
{
	const FVector2D ScreenCenter = PlayerCharacter->FindScreenCenter();

	FVector TraceStartLocation;
	FVector CameraDirection;
	PlayerCharacter->DeProjectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, TraceStartLocation, CameraDirection);
	const FVector TraceEndLocation = TraceStartLocation + CameraDirection * 1500.0f;
	
	TraceStartLocation = TraceStartLocation + CameraDirection * 200.0f;
	
	FHitResult HitResult;
	GetWorld()->SweepSingleByChannel(HitResult,TraceStartLocation,TraceEndLocation,FQuat::Identity,
		ECollisionChannel::ECC_Visibility,FCollisionShape::MakeCapsule(30,0));
	if(HitResult.bBlockingHit)
	{
		HookStartLocation = PlayerCharacter->GetActorLocation();
		HookEndLocation = HitResult.ImpactPoint + (CameraDirection*-35);
		bIsHooking = true;
		GetWorld()->GetTimerManager().SetTimer(HookPlayerMoveTimerHandle,this,&AGrapplingHook::HookMove,GetWorld()->DeltaTimeSeconds,true);
	}
}
void AGrapplingHook::HookMove()
{
	HookMoveCurveFloatValue += GetWorld()->DeltaTimeSeconds;
	if(HookPlayerMoveCurve->GetFloatValue(HookMoveCurveFloatValue) < 1.0f)
	{
		const FVector LerpVector = FMath::Lerp(HookStartLocation,HookEndLocation, HookPlayerMoveCurve->GetFloatValue(HookMoveCurveFloatValue));
		SetPoints(PlayerCharacter->GetActorLocation(), LerpVector);
	}
	else
		HookMoveEnd();
}
void AGrapplingHook::HookMoveEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(HookMoveTimerHandle);
	HookMoveCurveFloatValue = 0.0f;
	GetWorld()->GetTimerManager().SetTimer(HookPlayerMoveTimerHandle,this,&AGrapplingHook::HookPlayerMove,GetWorld()->DeltaTimeSeconds,true);
}
void AGrapplingHook::HookPlayerMove()
{
	HookPlayerMoveCurveFloatValue += GetWorld()->DeltaTimeSeconds;
	if(HookPlayerMoveCurve->GetFloatValue(HookPlayerMoveCurveFloatValue) < 1.0f)
	{
		FVector StartPoint = HookStartLocation;
		FVector EndPoint = HookEndLocation;
		StartPoint.Z += PlayerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		EndPoint.Z += PlayerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		const FVector LerpVector = FMath::Lerp(StartPoint,EndPoint, HookPlayerMoveCurve->GetFloatValue(HookPlayerMoveCurveFloatValue));
		PlayerCharacter->SetActorLocation(LerpVector);
	}
	else
		HookPlayerMoveEnd();
}
void AGrapplingHook::HookPlayerMoveEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(HookPlayerMoveTimerHandle);
	HookPlayerMoveCurveFloatValue = 0.0f;
	HookStartLocation = FVector::ZeroVector;
	HookEndLocation = FVector::ZeroVector;
	bIsHooking = false;
	
	PlayerCharacter->HookClass = nullptr;
	Destroy();
}
#pragma endregion Hook


#pragma region Mesh
void AGrapplingHook::SetPoints(const FVector StartLocation, const FVector EndLocation)
{
	const FVector StartPos =  UKismetMathLibrary::InverseTransformLocation(GetActorTransform(), StartLocation);
	const FVector EndPos =  UKismetMathLibrary::InverseTransformLocation(GetActorTransform(), EndLocation);

	SplineMesh->SetStartAndEnd(StartPos,FVector(0,0,0),EndPos,FVector(0,0,0));
}

#pragma endregion Mesh