// Copyright Epic Games, Inc. All Rights Reserved.

#include "InAppPerchase.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "InAppPerchaseUtil.h"
#define LOCTEXT_NAMESPACE "FInAppPerchaseModule"

void FInAppPerchaseModule::StartupModule()
{

}

void FInAppPerchaseModule::ShutdownModule()
{

}

TSharedPtr<FGetOfferingAsyncTask, ESPMode::ThreadSafe> FInAppPerchaseModule::GetOfferings()
{
	TSharedPtr<FGetOfferingAsyncTask, ESPMode::ThreadSafe> GetOfferingTask = MakeShared<FGetOfferingAsyncTask, ESPMode::ThreadSafe>();
#if PLATFORM_VISIONOS || PLATFORM_IOS
	[[RCPurchases sharedPurchases]getOfferingsWithCompletion:^ (RCOfferings * offerings, NSError * error) {
		if (offerings.current && offerings.current.availablePackages.count != 0) {
			for (int i = 0; i < offerings.current.availablePackages.count; i++) {
				NSLog(@"current offering = %@", offerings.current.availablePackages[i].identifier);
			}
			for (NSString* key in offerings.all.allKeys) {
				RCOffering* offering = offerings.all[key];
				NSLog(@"Key: %@, Value: %@", key, offering);
			}
            GetOfferingTask->Offerings = FOfferings::FromRCOfferings(offerings);
			GetOfferingTask->MarkDone();
		}
		else if (error) {
			FString Error([error localizedDescription]);
			NSLog(@"GetOffering Error!code = %ld", (long)error.code);
			UE_LOG(LogInApplePerchase, Error, TEXT("GetOfferings failed with error (%s)"), *Error);
			GetOfferingTask->SetErrorReason(Error);
		}
	}];
	printf("getOffering");
#endif

	return GetOfferingTask;
}

TSharedPtr<FPurchaseAsyncTask, ESPMode::ThreadSafe> FInAppPerchaseModule::Purchase(const FString& PackageId,const FString& Entitlement)
{
	TSharedPtr<FPurchaseAsyncTask, ESPMode::ThreadSafe> PurchaseTask = MakeShared<FPurchaseAsyncTask, ESPMode::ThreadSafe>();
    FString Id = PackageId;
    FString entitlement = Entitlement;
#if PLATFORM_VISIONOS || PLATFORM_IOS
	[[RCPurchases sharedPurchases]getOfferingsWithCompletion:^ (RCOfferings * offerings, NSError * error) {
		if (offerings.current && offerings.current.availablePackages.count != 0) {
            UE_LOG(LogInApplePerchase, Error, TEXT("Id =  (%s)"), *Id);
			RCPackage* package = nil;
			NSString* id = ConvertFString(Id);
			for (int i = 0; i < offerings.current.availablePackages.count; i++) {
				NSLog(@"current offering = %@", offerings.current.availablePackages[i].identifier);
				if (offerings.current.availablePackages[i].identifier == id)
				{
					package = offerings.current.availablePackages[i];
					break;
				}
			}
            if(package == nil)
            {
                FString Error("Can't find package!!");
                PurchaseTask->SetErrorReason(Error);
                return;
            }
			[[RCPurchases sharedPurchases]purchasePackage:package withCompletion : ^ (RCStoreTransaction * transaction, RCCustomerInfo * customerInfo, NSError * purchaseError, BOOL cancelled) {
                UE_LOG(LogInApplePerchase, Error, TEXT("entitlement =  (%s)"), *entitlement);

				if (cancelled)
				{
					FString Error("cancelled");
					NSLog(@"cancelled");
					PurchaseTask->bCancelled = cancelled;
					PurchaseTask->SetErrorReason(Error);
					return;
				}

				if (customerInfo.entitlements[ConvertFString(entitlement)].isActive) {
					FCustomerInfo CustomerInfo = FCustomerInfo::FromRCCustomerInfo(customerInfo);
					PurchaseTask->CustomerInfo = CustomerInfo;
					PurchaseTask->MarkDone();
					return;
				}
				else
				{
					FString Error("No entitlement!!");
					NSLog(@"No entitlement!!");
					UE_LOG(LogInApplePerchase, Error, TEXT("purchasePackage failed with error (%s)"), *Error);
					PurchaseTask->SetErrorReason(Error);
					return;
				}
				if (purchaseError)
				{
					FString Error([purchaseError localizedDescription]);
					NSLog(@"purchasePackage Error!code = %ld", (long)purchaseError.code);
					UE_LOG(LogInApplePerchase, Error, TEXT("purchasePackage failed with error (%s)"), *Error);
					PurchaseTask->SetErrorReason(Error);
				}
			}];}
		else if (error) {
			FString Error([error localizedDescription]);
			NSLog(@"GetOffering Error!code = %ld", (long)error.code);
			UE_LOG(LogInApplePerchase, Error, TEXT("GetOfferings failed with error (%s)"), *Error);
			PurchaseTask->SetErrorReason(Error);
		}
	}];

	printf("Purchase");
#endif
	return PurchaseTask;
}

TSharedPtr<FGetCustomerInfoAsyncTask, ESPMode::ThreadSafe> FInAppPerchaseModule::GetCustomerInfo()
{
	TSharedPtr<FGetCustomerInfoAsyncTask, ESPMode::ThreadSafe> GetCustomerInfoTask = MakeShared<FGetCustomerInfoAsyncTask, ESPMode::ThreadSafe>();
#if PLATFORM_VISIONOS || PLATFORM_IOS

	[[RCPurchases sharedPurchases]getCustomerInfoWithCompletion:^ (RCCustomerInfo * customerInfo, NSError * error) {
		if (error)
		{
			FString Error([error localizedDescription]);
			NSLog(@"GetOffering Error!code = %ld", (long)error.code);
			UE_LOG(LogInApplePerchase, Error, TEXT("GetCustomerInfo failed with error (%s)"), *Error);
			GetCustomerInfoTask->SetErrorReason(Error);
		}
		else
		{
            FCustomerInfo CustomerInfo = FCustomerInfo::FromRCCustomerInfo(customerInfo);
			GetCustomerInfoTask->CustomerInfo = CustomerInfo;
            GetCustomerInfoTask->MarkDone();
		}
    }];
	printf("GetCustomerInfo");
#endif
	return GetCustomerInfoTask;
}

TSharedPtr<FRestorePurchasesAsyncTask, ESPMode::ThreadSafe> FInAppPerchaseModule::RestorePurchases()
{
	TSharedPtr<FRestorePurchasesAsyncTask, ESPMode::ThreadSafe> RestorePurchasesTask = MakeShared<FRestorePurchasesAsyncTask, ESPMode::ThreadSafe>();
#if PLATFORM_VISIONOS || PLATFORM_IOS
	[[RCPurchases sharedPurchases]restorePurchasesWithCompletion:^ (RCCustomerInfo * customerInfo, NSError * error) {
		if (error)
		{
			FString Error([error localizedDescription]);
			NSLog(@"GetOffering Error!code = %ld", (long)error.code);
			UE_LOG(LogInApplePerchase, Error, TEXT("GetCustomerInfo failed with error (%s)"), *Error);
			RestorePurchasesTask->SetErrorReason(Error);
		}
		else
		{
			FCustomerInfo CustomerInfo = FCustomerInfo::FromRCCustomerInfo(customerInfo);
			RestorePurchasesTask->CustomerInfo = CustomerInfo;
			RestorePurchasesTask->MarkDone();
		}
	}];
	printf("RestorePurchases");
#endif
	return RestorePurchasesTask;
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FInAppPerchaseModule, InAppPerchase)

DEFINE_LOG_CATEGORY(LogInApplePerchase);

