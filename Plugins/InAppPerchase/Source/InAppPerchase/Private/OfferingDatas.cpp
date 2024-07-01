#include "OfferingDatas.h"
#include "Serialization/JsonReader.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "InAppPerchaseUtil.h"

#if PLATFORM_VISIONOS || PLATFORM_IOS

#define NS_TO_TCHAR(NS) UTF8_TO_TCHAR(NS.UTF8String)

FStoreTransaction FStoreTransaction::FromRCFStoreTransaction(RCStoreTransaction* storeTransaction)
{
    FStoreTransaction StoreTransaction;

    StoreTransaction.TransactionIdentifier = UTF8_TO_TCHAR(storeTransaction.transactionIdentifier.UTF8String);

    StoreTransaction.ProductIdentifier = UTF8_TO_TCHAR(storeTransaction.productIdentifier.UTF8String);

    StoreTransaction.PurchaseDate = ConvertNSDateToFDateTime(storeTransaction.purchaseDate);

    return StoreTransaction;
}

FEntitlementInfo FEntitlementInfo::FromRCEntitlementInfo(RCEntitlementInfo* entitlementInfo)
{
    FEntitlementInfo EntitlementInfo;
    
    EntitlementInfo.Identifier = UTF8_TO_TCHAR(entitlementInfo.identifier.UTF8String);
    
    EntitlementInfo.IsActive = entitlementInfo.isActive;
    
    EntitlementInfo.WillRenew = entitlementInfo.willRenew;
    
    EntitlementInfo.PeriodType = entitlementInfo.periodType;
    
    EntitlementInfo.LatestPurchaseDate = ConvertNSDateToFDateTime(entitlementInfo.latestPurchaseDate);
    
    EntitlementInfo.OriginalPurchaseDate = ConvertNSDateToFDateTime(entitlementInfo.originalPurchaseDate);
    
    EntitlementInfo.ExpirationDate = ConvertNSDateToFDateTime(entitlementInfo.expirationDate);
    
    EntitlementInfo.Store = entitlementInfo.store;
    
    EntitlementInfo.ProductIdentifier = UTF8_TO_TCHAR(entitlementInfo.productIdentifier.UTF8String);
    
    EntitlementInfo.IsSandbox = entitlementInfo.isSandbox;
    
    EntitlementInfo.UnsubscribeDetectedAt = ConvertNSDateToFDateTime(entitlementInfo.unsubscribeDetectedAt);
    
    EntitlementInfo.BillingIssueDetectedAt = ConvertNSDateToFDateTime(entitlementInfo.billingIssueDetectedAt);
    
    EntitlementInfo.Verification = static_cast<EVerificationResult>(entitlementInfo.verification);

    return EntitlementInfo;
}


FEntitlementInfos FEntitlementInfos::FromRCEntitlementInfos(RCEntitlementInfos* entitlementInfos)
{
    FEntitlementInfos EntitlementInfos;

    for (NSString* key in entitlementInfos.all) {
        RCEntitlementInfo* value = entitlementInfos.all[key];

        FString fstringKey(key.UTF8String);
        FEntitlementInfo fValue = FEntitlementInfo::FromRCEntitlementInfo(value);

        EntitlementInfos.All.Add(fstringKey, fValue);

        if(value.isActive)
            EntitlementInfos.Active.Add(fstringKey, fValue);
    }
    EntitlementInfos.Description = UTF8_TO_TCHAR(entitlementInfos.description.UTF8String);

    EntitlementInfos.Verification = static_cast<EVerificationResult>(entitlementInfos.verification);

    return EntitlementInfos;
}



FCustomerInfo FCustomerInfo::FromRCCustomerInfo(RCCustomerInfo * customerInfo)
{
    FCustomerInfo CustomerInfo;

    CustomerInfo.Entitlements = FEntitlementInfos::FromRCEntitlementInfos(customerInfo.entitlements);

    CustomerInfo.ActiveSubscriptions = ConvertNSSetToTArray(customerInfo.activeSubscriptions);

    CustomerInfo.AllPurchasedProductIdentifiers = ConvertNSSetToTArray(customerInfo.allPurchasedProductIdentifiers);

    CustomerInfo.LatestExpirationDate = ConvertNSDateToFDateTime(customerInfo.latestExpirationDate);

    CustomerInfo.FirstSeen = ConvertNSDateToFDateTime(customerInfo.firstSeen);

    CustomerInfo.OriginalAppUserId = UTF8_TO_TCHAR(customerInfo.originalAppUserId.UTF8String);

    CustomerInfo.RequestDate = ConvertNSDateToFDateTime(customerInfo.requestDate);

    CustomerInfo.OriginalPurchaseDate = ConvertNSDateToFDateTime(customerInfo.originalPurchaseDate);

    //TMap<FString, FDateTime> AllExpirationDates;

    //TMap<FString, FDateTime> AllPurchaseDates;

    CustomerInfo.OriginalApplicationVersion = UTF8_TO_TCHAR(customerInfo.originalApplicationVersion.UTF8String);

    CustomerInfo.ManagementURL = ConvertNSURLToFString(customerInfo.managementURL);

    for (RCStoreTransaction* obj in customerInfo.nonSubscriptionTransactions) {
        CustomerInfo.NonSubscriptionTransactions.Emplace(FStoreTransaction::FromRCFStoreTransaction(obj));
    }
    return CustomerInfo;
    
}


FRCPackage FRCPackage::FromRCPackage(RCPackage* package)
{
    FRCPackage Package;    
    if (package)
    {
        Package.Identifier = NS_TO_TCHAR(package.identifier);

        Package.PackageType = static_cast<EPackageType>(package.packageType);

        Package.StoreProduct = FStoreProduct::FromRCStoreProduct(package.storeProduct);

        Package.PresentedOfferingContext = FPresentedOfferingContext::FromRCPresentedOfferingContext(package.presentedOfferingContext);
    }
    return Package;
}

FOffering FOffering::FromRCOffering(RCOffering* offering)
{
    FOffering Offering;
    if (offering)
    {
        Offering.Identifier = NS_TO_TCHAR(offering.identifier);
        
        Offering.ServerDescription = NS_TO_TCHAR(offering.serverDescription);
        
        for (RCPackage* obj in offering.availablePackages) {
            FRCPackage Package = FRCPackage::FromRCPackage(obj);
            Offering.AvailablePackages.Emplace(Package);
        }

        //TMap<FString, UObject*> Metadata;
        
        Offering.Lifetime = FRCPackage::FromRCPackage(offering.lifetime);
        
        Offering.Annual = FRCPackage::FromRCPackage(offering.annual);
        
        Offering.SixMonth = FRCPackage::FromRCPackage(offering.sixMonth);
        
        Offering.ThreeMonth = FRCPackage::FromRCPackage(offering.threeMonth);
        
        Offering.TwoMonth = FRCPackage::FromRCPackage(offering.twoMonth);
        
        Offering.Monthly = FRCPackage::FromRCPackage(offering.monthly);
        
        Offering.Weekly = FRCPackage::FromRCPackage(offering.weekly);
    }
    return Offering;
}


FOfferings FOfferings::FromRCOfferings(RCOfferings* offerings)
{
    FOfferings Offerings;
    if (offerings)
    {
        TMap<FString, FOffering> All;

        for (NSString* key in offerings.all) {
            RCOffering* value = offerings.all[key];
            Offerings.All.Add(NS_TO_TCHAR(key), FOffering::FromRCOffering(value));
        }
        Offerings.Current = FOffering::FromRCOffering(offerings.current);
    }
    return Offerings;
}

FStoreProduct FStoreProduct::FromRCStoreProduct(RCStoreProduct* product)
{
    FStoreProduct StoreProduct;

    if (product)
    {
        StoreProduct.Title = NS_TO_TCHAR(product.localizedTitle);
        
        StoreProduct.Identifier = NS_TO_TCHAR(product.productIdentifier);
        
        StoreProduct.Description = NS_TO_TCHAR(product.localizedDescription);
        
        //StoreProduct.Price = product.price;
        
        StoreProduct.PriceFString = NS_TO_TCHAR(product.localizedPriceString);
        
        StoreProduct.CurrencyCode = NS_TO_TCHAR(product.currencyCode);
        
        //StoreProduct.IntroductoryPrice = FIntroductoryPrice::FromRCIntroductoryPrice(product.introductoryPrice);
        
        StoreProduct.ProductCategory = static_cast<EProductCategory>(product.productCategory);
        
        //StoreProduct.DefaultOption = FSubscriptionOption::FromRCSubscriptionOption(product.subscriptionOption);
        /*
        for (RCSubscriptionOption* obj in product.subscriptionOptions) {
            FSubscriptionOption SubscriptionOption = FSubscriptionOption::FromRCSubscriptionOption(obj);
            StoreProduct.SubscriptionOptions.Emplace(SubscriptionOption);
        }
        
        StoreProduct.PresentedOfferingContext = FPresentedOfferingContext::FromRCPresentedOfferingContext(product.presentedOfferingContext);
        
        for (RCDiscount* obj in product.discounts) {
            FDiscount Discount = FDiscount::FromRCDiscount(obj);
            StoreProduct.Discounts.Emplace(Discount);
        }
       
        StoreProduct.SubscriptionPeriod = NS_TO_TCHAR(product.subscriptionPeriod);*/
    }

    return StoreProduct;
}


/*
FIntroductoryPrice FIntroductoryPrice::FromRCIntroductoryPrice(RCIntroductoryPrice* introductoryPrice)
{
    FIntroductoryPrice IntroductoryPrice;
    if (introductoryPrice)
    {
        IntroductoryPrice.Price = introductoryPrice.price;
        
        IntroductoryPrice.PriceString = NS_TO_TCHAR(introductoryPrice.priceString);
        
        IntroductoryPrice.Period = NS_TO_TCHAR(introductoryPrice.period);
        
        IntroductoryPrice.Unit = NS_TO_TCHAR(introductoryPrice.unit);
        
        int NumberOfUnits = introductoryPrice.numberOfUnits;
        
        int Cycles = introductoryPrice.cycles;
    }
    return IntroductoryPrice;
}*/

FPeriod FPeriod::FromRCPeriod(RCSubscriptionPeriod* period)
{
    FPeriod Period;
    if (period)
    {
        Period.Unit = static_cast<EPeriodUnit>(period.unit);
        Period.Value = period.value;
        //Period.ISO8601 = NS_TO_TCHAR(period.ISO8601);
    }
    return Period;
}

FDiscount FDiscount::FromRCDiscount(RCStoreProductDiscount* discount)
{
    FDiscount Discount;
    if (discount)
    {
        Discount.Identifier = NS_TO_TCHAR(discount.offerIdentifier);
        
        Discount.Price = [discount.price floatValue];
        
        Discount.PriceString = NS_TO_TCHAR(discount.localizedPriceString);
        
        //Discount.Cycles = discount.cycles;
        
        //Discount.Period = NS_TO_TCHAR(discount.subscriptionPeriod);
        
        //Discount.PeriodUnit = NS_TO_TCHAR(discount.periodUnit);
        
        //Discount.PeriodNumberOfUnits = discount.periodNumberOfUnits;
    }
    return Discount;
}

FPresentedOfferingTargetingCtx FPresentedOfferingTargetingCtx::FromRCPresentedOfferingTargetingContext(RCTargetingContext* context)
{
    FPresentedOfferingTargetingCtx PresentedOfferingTargetingCtx;
    if (context)
    {
        PresentedOfferingTargetingCtx.Revision = context.revision;
        PresentedOfferingTargetingCtx.RuleId = NS_TO_TCHAR(context.ruleId);
    }
    return PresentedOfferingTargetingCtx;
}

FPresentedOfferingContext FPresentedOfferingContext::FromRCPresentedOfferingContext(RCPresentedOfferingContext* context)
{
    FPresentedOfferingContext PresentedOfferingContext;
    if (context)
    {
        PresentedOfferingContext.OfferingIdentifier = NS_TO_TCHAR(context.offeringIdentifier);
        PresentedOfferingContext.PlacementIdentifier = NS_TO_TCHAR(context.placementIdentifier);
        PresentedOfferingContext.TargetingContext = FPresentedOfferingTargetingCtx::FromRCPresentedOfferingTargetingContext(context.targetingContext);
    }
    return PresentedOfferingContext;
}
/*
FPricingPhase FPricingPhase::FromRCPricingPhase(RCPricingPhase* pricingPhase)
{
    FPricingPhase PricingPhase;
    if (pricingPhase)
    {
        PricingPhase.BillingPeriod = FPeriod::FromRCPeriod(pricingPhase.billingPeriod);
        
        PricingPhase.RecurrenceMode = static_cast<ERecurrenceMode>(pricingPhase.recurrenceMode);
        
        PricingPhase.BillingCycleCount = pricingPhase.billingCycleCount;
        
        //PricingPhase.Price = FPrice::FromRCPrice(pricingPhase.price);
        
        PricingPhase.OfferPaymentMode = static_cast<EOfferPaymentMode>(pricingPhase.offerPaymentMode);
    }
    return PricingPhase;
}

FPrice FPrice::FromRCPrice(RCPrice* price)
{
    FPrice Price;
    if (price)
    {
        Price.Formatted = NS_TO_TCHAR(price.formatted);
        Price.AmountMicros = price.amountMicros;
        Price.CurrencyCode = NS_TO_TCHAR(price.currencyCode);
    }
    return Price;
}

FSubscriptionOption FSubscriptionOption::FromRCSubscriptionOption(RCSubscriptionOption* subscriptionOption)
{
    FSubscriptionOption SubscriptionOption;
    if (subscriptionOption)
    {
        SubscriptionOption.Id = NS_TO_TCHAR(subscriptionOption.id);
        
        SubscriptionOption.StoreProductId = NS_TO_TCHAR(subscriptionOption.id);
        
        SubscriptionOption.ProductId = NS_TO_TCHAR(subscriptionOption.id);
        
        for (RCPricingPhase* obj in subscriptionOption.pricingPhases) {
            //SubscriptionOption.PricingPhases.Emplace(FPricingPhase::FromRCPricingPhase(obj));
        }

        SubscriptionOption.Tags = ConvertNSSetToTArray(subscriptionOption.tags);
        
        SubscriptionOption.IsBasePlan = subscriptionOption.;
        
        SubscriptionOption.BillingPeriod = FPeroid::FromRCPeriod(subscriptionOption.billingPeroid);
        
        SubscriptionOption.IsPrepaid = subscriptionOption.isPrepaid;
        
        //SubscriptionOption.FullPricePhase = FPricingPhase::FromRCPricingPhase(subscriptionOption.fullPricePhase);
        
        SubscriptionOption.FreePhase = FPricingPhase::FromRCPricingPhase(subscriptionOption.freePhase);;
        
        SubscriptionOption.IntroPhase = FPricingPhase::FromRCPricingPhase(subscriptionOption.introPhase);;
        
        SubscriptionOption.PresentedOfferingContext = FPresentedOfferingContext::FromRCPresentedOfferingContext(subscriptionOption.presentedOfferingContext);
    }
    return SubscriptionOption;
}

 */
#endif
