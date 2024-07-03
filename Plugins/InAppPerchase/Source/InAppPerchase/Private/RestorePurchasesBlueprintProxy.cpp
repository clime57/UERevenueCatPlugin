// Copyright Epic Games, Inc. All Rights Reserved.

#include "RestorePurchasesBlueprintProxy.h"
#include "InAppPerchase.h"


URestorePurchasesAsyncTaskProxy::URestorePurchasesAsyncTaskProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bShouldTick(true)
{
}

void URestorePurchasesAsyncTaskProxy::Tick(float DeltaTime)
{
	if (!AsyncTask.IsValid())
	{
		bShouldTick = false;
		OnFailure.Broadcast(CustomerInfo);
		return;
	}

	if (AsyncTask->IsDone())
	{
		bShouldTick = false;
		// Fire the right delegate
		if (!AsyncTask->HadError())
		{
			CustomerInfo = AsyncTask->GetCustomerInfo();
			OnSuccess.Broadcast(CustomerInfo);
		}
		else
		{
			OnFailure.Broadcast(CustomerInfo);
		}
	}
}

URestorePurchasesAsyncTaskProxy* URestorePurchasesAsyncTaskProxy::CreateProxyObjectForRestorePurchases()
{
	URestorePurchasesAsyncTaskProxy* Proxy = NewObject<URestorePurchasesAsyncTaskProxy>();
	Proxy->SetFlags(RF_StrongRefOnFrame);
	Proxy->AsyncTask = IInAppPerchaseModule::Get().RestorePurchases();

	return Proxy;
}
