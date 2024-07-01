#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Engine/EngineTypes.h"
#include "Tickable.h"
#include "OfferingDatas.h"
#include "GetOfferingsBlueprintProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetOfferingsDelegate, const FOfferings&, Offerings);

class FGetOfferingAsyncTask;

UCLASS()
class INAPPPERCHASE_API UGetOfferingsAsyncTaskProxy :
	public UObject,
	public FTickableGameObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FGetOfferingsDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetOfferingsDelegate OnFailure;


	UFUNCTION(BlueprintCallable, Meta = (BlueprintInternalUseOnly = "true"),Category="InAppPerchase")
	static UGetOfferingsAsyncTaskProxy* CreateProxyObjectForGetOfferings();


	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return bShouldTick; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UGetOfferingsAsyncTaskProxy, STATGROUP_Tickables); }

	TSharedPtr<FGetOfferingAsyncTask, ESPMode::ThreadSafe> AsyncTask;

	UPROPERTY(BlueprintReadOnly, Category="Apple Vision")
	FOfferings Offerings;

private:
	bool bShouldTick;
};
