#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Engine/EngineTypes.h"
#include "Tickable.h"
#include "OfferingDatas.h"
#include "RestorePurchasesBlueprintProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRestorePurchasesDelegate, const FCustomerInfo&, CustomerInfo);

class FRestorePurchasesAsyncTask;

UCLASS()
class INAPPPERCHASE_API URestorePurchasesAsyncTaskProxy :
	public UObject,
	public FTickableGameObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FRestorePurchasesDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRestorePurchasesDelegate OnFailure;


	UFUNCTION(BlueprintCallable, Meta = (BlueprintInternalUseOnly = "true"),Category="InAppPerchase")
	static URestorePurchasesAsyncTaskProxy* CreateProxyObjectForRestorePurchases();


	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return bShouldTick; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(URestorePurchasesAsyncTaskProxy, STATGROUP_Tickables); }

	TSharedPtr<FRestorePurchasesAsyncTask, ESPMode::ThreadSafe> AsyncTask;

	UPROPERTY(BlueprintReadOnly, Category="InAppPerchase")
	FCustomerInfo CustomerInfo;

private:
	bool bShouldTick;
};
