// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(RogueDoom, Log, All);
#define ROGUEDOOM_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ROGUEDOOM_S(Verbosity) UE_LOG(RogueDoom, Verbosity, TEXT("%s"), *ROGUEDOOM_CALLINFO)
#define ROGUEDOOM(Verbosity, Format, ...) UE_LOG(RogueDoom, Verbosity, TEXT("%s %s"), *ROGUEDOOM_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))