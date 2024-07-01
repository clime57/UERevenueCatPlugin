// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "OfferingDatas.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInApplePerchase, Log, All);

class FGetOfferingAsyncTask;
class FPurchaseAsyncTask;
class FGetCustomerInfoAsyncTask;
class IInAppPerchaseModule : public IModuleInterface
{
public:

	static inline IInAppPerchaseModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IInAppPerchaseModule>("InAppPerchase");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("InAppPerchase");
	}

	virtual TSharedPtr<FGetOfferingAsyncTask, ESPMode::ThreadSafe> GetOfferings() = 0;

	virtual TSharedPtr<FPurchaseAsyncTask, ESPMode::ThreadSafe> Purchase(const FString& PackageId,const FString& Entitlement) = 0;

	virtual TSharedPtr<FGetCustomerInfoAsyncTask, ESPMode::ThreadSafe> GetCustomerInfo() = 0;
private:
};

class FInAppPerchaseModule : public IInAppPerchaseModule
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


	virtual TSharedPtr<FGetOfferingAsyncTask, ESPMode::ThreadSafe> GetOfferings() override;

	virtual TSharedPtr<FPurchaseAsyncTask, ESPMode::ThreadSafe> Purchase(const FString& PackageId,const FString& Entitlement) override;

	virtual TSharedPtr<FGetCustomerInfoAsyncTask, ESPMode::ThreadSafe> GetCustomerInfo() override;
private:
};


class INAPPPERCHASE_API FAppleAsyncTaskBase
{
protected:
	FAppleAsyncTaskBase() {}
	virtual ~FAppleAsyncTaskBase() {}

public:
	bool IsDone() const { return bIsDone; }
	bool HadError() const { return bHadError; }
	FString GetErrorReason() const { return Error; }

protected:
	FThreadSafeBool bIsDone;
	FThreadSafeBool bHadError;
	FString Error;
};

class INAPPPERCHASE_API FGetOfferingAsyncTask : public FAppleAsyncTaskBase
{
public:
	void SetErrorReason(const FString& InError)
	{
		Error = InError;
		bHadError = true;
		bIsDone = true;
	}
	void MarkDone() { bIsDone = true; }

	FOfferings& GetOffering()
	{
		return Offerings;
	}
public:
	FOfferings Offerings;
};

class INAPPPERCHASE_API FPurchaseAsyncTask : public FAppleAsyncTaskBase
{
public:
	void SetErrorReason(const FString& InError)
	{
		Error = InError;
		bHadError = true;
		bIsDone = true;
	}
	void MarkDone() { bIsDone = true; }

public:
};

class INAPPPERCHASE_API FGetCustomerInfoAsyncTask : public FAppleAsyncTaskBase
{
public:
	void SetErrorReason(const FString& InError)
	{
		Error = InError;
		bHadError = true;
		bIsDone = true;
	}
	void MarkDone() { bIsDone = true; }

	FCustomerInfo& GetCustomerInfo()
	{
		return CustomerInfo;
	}
public:
	FCustomerInfo CustomerInfo;
};
