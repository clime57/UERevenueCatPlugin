#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Engine/EngineTypes.h"
#include "Tickable.h"
#include "OfferingDatas.h"
#include "PurchaseBlueprintProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPurchaseDelegate,const FCustomerInfo&, CustomerInfo,const bool, bCancelled);

class FPurchaseAsyncTask;

UCLASS()
class INAPPPERCHASE_API UPurchaseAsyncTaskProxy :
	public UObject,
	public FTickableGameObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FPurchaseDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FPurchaseDelegate OnFailure;


	UFUNCTION(BlueprintCallable, Meta = (BlueprintInternalUseOnly = "true"),Category="InAppPerchase")
	static UPurchaseAsyncTaskProxy* CreateProxyObjectForPurchase(const FString& PackageId,const FString& Entitlement);


	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return bShouldTick; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UPurchaseAsyncTaskProxy, STATGROUP_Tickables); }

	TSharedPtr<FPurchaseAsyncTask, ESPMode::ThreadSafe> AsyncTask;

	UPROPERTY(BlueprintReadOnly, Category = "InAppPerchase")
	FCustomerInfo CustomerInfo;
private:
	bool bShouldTick;
};
