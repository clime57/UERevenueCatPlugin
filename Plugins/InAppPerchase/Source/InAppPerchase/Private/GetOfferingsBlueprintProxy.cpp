// Copyright Epic Games, Inc. All Rights Reserved.

#include "GetOfferingsBlueprintProxy.h"
#include "InAppPerchase.h"

UGetOfferingsAsyncTaskProxy::UGetOfferingsAsyncTaskProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bShouldTick(true)
{
}

void UGetOfferingsAsyncTaskProxy::Tick(float DeltaTime)
{
	if (!AsyncTask.IsValid())
	{
		bShouldTick = false;
		OnFailure.Broadcast(Offerings);
		return;
	}

	if (AsyncTask->IsDone())
	{
		bShouldTick = false;
		// Fire the right delegate
		if (!AsyncTask->HadError())
		{
			Offerings = AsyncTask->GetOffering();
            for (auto offering : Offerings.Current.AvailablePackages)
            {
                UE_LOG(LogInApplePerchase, Log, TEXT("%s"), *offering.Identifier);
            }
			OnSuccess.Broadcast(Offerings);
		}
		else
		{
			OnFailure.Broadcast(Offerings);
		}
	}
}

UGetOfferingsAsyncTaskProxy* UGetOfferingsAsyncTaskProxy::CreateProxyObjectForGetOfferings()
{
	UGetOfferingsAsyncTaskProxy* Proxy = NewObject<UGetOfferingsAsyncTaskProxy>();
	Proxy->SetFlags(RF_StrongRefOnFrame);
	Proxy->AsyncTask = IInAppPerchaseModule::Get().GetOfferings();

	return Proxy;
}
