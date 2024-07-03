// Copyright Epic Games, Inc. All Rights Reserved.

#include "InAppPerchaseBlueprintSupport.h"
#include "GetOfferingsBlueprintProxy.h"
#include "PurchaseBlueprintProxy.h"
#include "GetCustomerInfoBlueprintProxy.h"
#include "RestorePurchasesBlueprintProxy.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, InAppPerchaseBlueprintSupport)

UK2Node_GetOfferings::UK2Node_GetOfferings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ProxyFactoryFunctionName = GET_FUNCTION_NAME_CHECKED(UGetOfferingsAsyncTaskProxy, CreateProxyObjectForGetOfferings);
	ProxyFactoryClass = UGetOfferingsAsyncTaskProxy::StaticClass();
	ProxyClass = UGetOfferingsAsyncTaskProxy::StaticClass();
}

UK2Node_Purchase::UK2Node_Purchase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ProxyFactoryFunctionName = GET_FUNCTION_NAME_CHECKED(UPurchaseAsyncTaskProxy, CreateProxyObjectForPurchase);
	ProxyFactoryClass = UPurchaseAsyncTaskProxy::StaticClass();
	ProxyClass = UPurchaseAsyncTaskProxy::StaticClass();
}

UK2Node_GetCustomerInfo::UK2Node_GetCustomerInfo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ProxyFactoryFunctionName = GET_FUNCTION_NAME_CHECKED(UGetCustomerInfoAsyncTaskProxy, CreateProxyObjectForGetCustomerInfo);
	ProxyFactoryClass = UGetCustomerInfoAsyncTaskProxy::StaticClass();
	ProxyClass = UGetCustomerInfoAsyncTaskProxy::StaticClass();
}

UK2Node_RestorePurchases::UK2Node_RestorePurchases(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ProxyFactoryFunctionName = GET_FUNCTION_NAME_CHECKED(URestorePurchasesAsyncTaskProxy, CreateProxyObjectForRestorePurchases);
	ProxyFactoryClass = URestorePurchasesAsyncTaskProxy::StaticClass();
	ProxyClass = URestorePurchasesAsyncTaskProxy::StaticClass();
}