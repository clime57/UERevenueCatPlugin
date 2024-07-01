// Fill out your copyright notice in the Description page of Project Settings.

#include "IAPBlueprintFunctionLibrary.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "InAppPerchaseUtil.h"

#if PLATFORM_VISIONOS || PLATFORM_IOS
#import <StoreKit/StoreKit.h>
#import "RevenueCat/RevenueCat-Swift.h"
#endif


bool UIAPBlueprintFunctionLibrary::InitIAP(const FString& APIKey, const FString& UserId)
{
#if PLATFORM_VISIONOS || PLATFORM_IOS
    RCPurchases.logLevel = RCLogLevelDebug;
    [RCPurchases configureWithAPIKey : ConvertFString(APIKey) appUserID : ConvertFString(UserId)] ;
#endif
    return true;
}

