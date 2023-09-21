// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(UE_CombatPlane_lec, Log, All);

// �α׸� �� �Լ���� �� �αװ� ��ġ�� ���� ���
#define CPLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

// �α׸� UE_LOG�� �� ���� ������ �Ʒ��� ���� Ŀ���� �α׸� �����ϸ� �ʿ��� ������ �� �� �ִ�.
#define CPLOG_S(Verbosity) UE_LOG(UE_CombatPlane_lec, Verbosity, TEXT("%s"), *CPLOG_CALLINFO)

// �ش� �࿡�� ������ �� �ִ� ���� ���� �α׷� ����ϰ� ������ ���� �α� ��ũ�θ� ���.
#define CPLOG(Verbosity, Format, ...) UE_LOG(UE_CombatPlane_lec, Verbosity, TEXT("%s%s"), *CPLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

// ������ ���� �ƴϸ� Error �αװ� �ߵ��� ����
#define CPCHECK(Expr, ...)	{ if(!(Expr)) {CPLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; }}