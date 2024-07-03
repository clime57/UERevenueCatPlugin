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
		OnFailure.Broadcast(CustomerInfo,false);
		return;
	}

	if (AsyncTask->IsDone())
	{
		bShouldTick = false;
		CustomerInfo = AsyncTask->GetCustomerInfo();
		bool bIsCanceled = AsyncTask->IsCancelled();
		if (!AsyncTask->HadError())
		{
			OnSuccess.Broadcast(CustomerInfo,bIsCanceled);
		}
		else
		{
			OnFailure.Broadcast(CustomerInfo, bIsCanceled);
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
