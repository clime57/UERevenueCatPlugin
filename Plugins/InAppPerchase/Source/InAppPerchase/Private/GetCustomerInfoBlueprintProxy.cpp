// Copyright Epic Games, Inc. All Rights Reserved.

#include "GetCustomerInfoBlueprintProxy.h"
#include "InAppPerchase.h"


UGetCustomerInfoAsyncTaskProxy::UGetCustomerInfoAsyncTaskProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bShouldTick(true)
{
}

void UGetCustomerInfoAsyncTaskProxy::Tick(float DeltaTime)
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

UGetCustomerInfoAsyncTaskProxy* UGetCustomerInfoAsyncTaskProxy::CreateProxyObjectForGetCustomerInfo()
{
	UGetCustomerInfoAsyncTaskProxy* Proxy = NewObject<UGetCustomerInfoAsyncTaskProxy>();
	Proxy->SetFlags(RF_StrongRefOnFrame);
	Proxy->AsyncTask = IInAppPerchaseModule::Get().GetCustomerInfo();

	return Proxy;
}
