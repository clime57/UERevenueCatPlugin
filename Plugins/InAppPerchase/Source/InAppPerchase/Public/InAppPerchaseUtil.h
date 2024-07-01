// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_VISIONOS || PLATFORM_IOS

NSString* ConvertFString(const FString UEString);

TArray<FString> ConvertNSSetToTArray(NSSet<NSString *> * _Nonnull stringSet);

FDateTime ConvertNSDateToFDateTime(NSDate* date);

FString ConvertNSURLToFString(NSURL* url);

#endif
