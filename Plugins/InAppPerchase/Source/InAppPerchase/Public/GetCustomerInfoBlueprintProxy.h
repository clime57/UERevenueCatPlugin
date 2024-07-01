#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Engine/EngineTypes.h"
#include "Tickable.h"
#include "OfferingDatas.h"
#include "GetCustomerInfoBlueprintProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetCustomerInfoDelegate, const FCustomerInfo&, CustomerInfo);

class FGetCustomerInfoAsyncTask;

UCLASS()
class INAPPPERCHASE_API UGetCustomerInfoAsyncTaskProxy :
	public UObject,
	public FTickableGameObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FGetCustomerInfoDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetCustomerInfoDelegate OnFailure;


	UFUNCTION(BlueprintCallable, Meta = (BlueprintInternalUseOnly = "true"),Category="InAppPerchase")
	static UGetCustomerInfoAsyncTaskProxy* CreateProxyObjectForGetCustomerInfo();


	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return bShouldTick; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UGetCustomerInfoAsyncTaskProxy, STATGROUP_Tickables); }

	TSharedPtr<FGetCustomerInfoAsyncTask, ESPMode::ThreadSafe> AsyncTask;

	UPROPERTY(BlueprintReadOnly, Category="InAppPerchase")
	FCustomerInfo CustomerInfo;

private:
	bool bShouldTick;
};
