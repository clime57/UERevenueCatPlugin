// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurchaseBlueprintProxy.h"
#include "InAppPerchase.h"


UPurchaseAsyncTaskProxy::UPurchaseAsyncTaskProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bShouldTick(true)
{
}

void UPurchaseAsyncTaskProxy::Tick(float DeltaTime)
{
	if (!AsyncTask.IsValid())
	{
		bShouldTick = false;
		OnFailure.Broadcast();
		return;
	}

	if (AsyncTask->IsDone())
	{
		bShouldTick = false;
		// Fire the right delegate
		if (!AsyncTask->HadError())
		{
			OnSuccess.Broadcast();
		}
		else
		{
			OnFailure.Broadcast();
		}
	}
}

UPurchaseAsyncTaskProxy* UPurchaseAsyncTaskProxy::CreateProxyObjectForPurchase(const FString& PackageId,const FString& Entitlement)
{
	UPurchaseAsyncTaskProxy* Proxy = NewObject<UPurchaseAsyncTaskProxy>();
	Proxy->SetFlags(RF_StrongRefOnFrame);
	Proxy->AsyncTask = IInAppPerchaseModule::Get().Purchase(PackageId,Entitlement);

	return Proxy;
}
