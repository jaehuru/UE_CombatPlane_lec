// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_KeyInput.h"

ACP_Pawn_KeyInput::ACP_Pawn_KeyInput()
{
	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	
	pSpringArm->SetupAttachment(pMeshComp);
	pCamera->SetupAttachment(pSpringArm);
	pCamera->SetRelativeLocation(FVector::ZeroVector);

	pSpringArm->TargetArmLength = 1000.f;
	pSpringArm->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 150.f), DefaultSpringArmRotation);
}

void ACP_Pawn_KeyInput::BeginPlay()
{
	Super::BeginPlay();
}

void ACP_Pawn_KeyInput::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocalOffset(FVector(100.f, 0.f, 0.f));
	
	FRotator DeltaRotation;

	StabilizeRoll(_DeltaTime);
	DeltaRotation.Pitch = CurrentSpeed_Pitch * _DeltaTime;
	DeltaRotation.Yaw = CurrentSpeed_Yaw * _DeltaTime;
	DeltaRotation.Roll = CurrentSpeed_Roll * _DeltaTime;

	AddActorLocalRotation(DeltaRotation);

	pSpringArm->AddLocalRotation(0.1f * DeltaRotation.GetInverse());
	StabilizeSpringArm(_DeltaTime);
}

void ACP_Pawn_KeyInput::SetupPlayerInputComponent(UInputComponent* _InputComponent)
{
	Super::SetupPlayerInputComponent(_InputComponent);

	_InputComponent->BindAxis(TEXT("LookUp"), this, &ACP_Pawn_KeyInput::ProceessPitch);
	_InputComponent->BindAxis(TEXT("TrunAround"), this, &ACP_Pawn_KeyInput::ProceessYaw);
}

void ACP_Pawn_KeyInput::ProceessPitch(float _Value)
{
	const float TargetSpeed_Pitch = _Value * AxisSpeed;
	CurrentSpeed_Pitch = FMath::FInterpTo(CurrentSpeed_Pitch, TargetSpeed_Pitch, GetWorld()->DeltaTimeSeconds, 2.f);
}

void ACP_Pawn_KeyInput::ProceessYaw(float _Value)
{
	const float TargetSpeed_Yaw = _Value * AxisSpeed;
	CurrentSpeed_Yaw = FMath::FInterpTo(CurrentSpeed_Yaw, TargetSpeed_Yaw, GetWorld()->DeltaTimeSeconds, 2.f);

	const float TargetSpeed_Roll = _Value * AxisSpeed;
	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, GetWorld()->DeltaTimeSeconds, 2.f);
}

void ACP_Pawn_KeyInput::StabilizeRoll(float _DeltaTime)
{
	const float CurrentAngle_Roll = GetActorRotation().Roll;
	const float TargetSpeed_Roll = -CurrentAngle_Roll * 1.f;

	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, _DeltaTime, 1.f);
}

void ACP_Pawn_KeyInput::StabilizeSpringArm(float _DeltaTime)
{
	if (pSpringArm->GetRelativeRotation() != DefaultSpringArmRotation)
		pSpringArm->SetRelativeRotation(FMath::RInterpTo(pSpringArm->GetRelativeRotation(), DefaultSpringArmRotation, _DeltaTime, 1.f));
}
