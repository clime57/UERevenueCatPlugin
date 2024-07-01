// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#if PLATFORM_VISIONOS || PLATFORM_IOS
#import <StoreKit/StoreKit.h>
#import "RevenueCat/RevenueCat-Swift.h"
#endif

#include "OfferingDatas.generated.h"




/**
 *
 */
UENUM()
enum class /*INAPPPERCHASE_API*/ EPeriodUnit : uint8
{
    DAY = 0,

    WEEK = 1,

    MONTH = 2,

    YEAR = 3,

    UNKNOWN = 4
};


/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FPeriod
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(BlueprintReadOnly)
    EPeriodUnit Unit;

    /**
    * The increment of time that a subscription period is specified in
    */
    UPROPERTY(BlueprintReadOnly)
    int Value;

    /**
    * Specified in ISO 8601 format. For example, P1W equates to one week,
    * P1M equates to one month, P3M equates to three months, P6M equates to six months,
    * and P1Y equates to one year
    */
    UPROPERTY(BlueprintReadOnly)
    FString ISO8601;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FPeriod FromRCPeriod(RCSubscriptionPeriod* period);
#endif
};

USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FDiscount
{
    GENERATED_USTRUCT_BODY()
    /// <summary>
 /// Identifier of the discount.
 /// </summary>
    UPROPERTY(BlueprintReadOnly)
    FString Identifier;

    /// <summary>
    /// Price in the local currency.
    /// </summary>
    UPROPERTY(BlueprintReadOnly)
    float Price;

    /// <summary>
    /// Formatted price, including its currency sign, such as €3.99.
    /// </summary>
    UPROPERTY(BlueprintReadOnly)
    FString PriceString;

    /// <summary>
    /// Number of subscription billing periods for which the user will be given the discount, such as 3.
    /// </summary>
    UPROPERTY(BlueprintReadOnly)
    int Cycles;

    /// <summary>
    /// Billing period of the discount, specified in ISO 8601 format.
    /// </summary>
    UPROPERTY(BlueprintReadOnly)
    FString Period;

    /// <summary>
    /// Unit for the billing period of the discount, can be DAY, WEEK, MONTH or YEAR.
    /// </summary>
    UPROPERTY(BlueprintReadOnly)
    FString PeriodUnit;

    /// <summary>
    /// Number of units for the billing period of the discount.
    /// </summary>
    UPROPERTY(BlueprintReadOnly)
    int PeriodNumberOfUnits;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FDiscount FromRCDiscount(RCStoreProductDiscount* discount);
#endif
};


/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FPresentedOfferingTargetingCtx
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(BlueprintReadOnly)
    int Revision;
    UPROPERTY(BlueprintReadOnly)
    FString RuleId;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FPresentedOfferingTargetingCtx FromRCPresentedOfferingTargetingContext(RCTargetingContext* context);
#endif
};
/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FPresentedOfferingContext
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(BlueprintReadOnly)
    FString OfferingIdentifier;
    UPROPERTY(BlueprintReadOnly)
    FString PlacementIdentifier;
    UPROPERTY(BlueprintReadOnly)
    FPresentedOfferingTargetingCtx TargetingContext;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FPresentedOfferingContext FromRCPresentedOfferingContext(RCPresentedOfferingContext* context);
#endif
};

/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FIntroductoryPrice
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(BlueprintReadOnly)
    float Price;
    UPROPERTY(BlueprintReadOnly)
    FString PriceString;
    UPROPERTY(BlueprintReadOnly)
    FString Period;
    UPROPERTY(BlueprintReadOnly)
    FString Unit;
    UPROPERTY(BlueprintReadOnly)
    int NumberOfUnits;
    UPROPERTY(BlueprintReadOnly)
    int Cycles;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    //static FIntroductoryPrice FromRCIntroductoryPrice(CIntroductoryPrice* introductoryPrice);
#endif
};

UENUM()
enum class EProductCategory : uint8
{
    /// A type of product for non-subscription.
    NON_SUBSCRIPTION = 0,

    /// A type of product for subscriptions.
    SUBSCRIPTION = 1,

    /// The user is eligible for a free trial or intro pricing for this product.
    UNKNOWN = 2
};


/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FPrice
{
    GENERATED_USTRUCT_BODY()
    /**
 * Formatted price of the item, including its currency sign. For example $3.00
 */
    UPROPERTY(BlueprintReadOnly)
    FString Formatted;

    /**
    * Price in micro-units, where 1,000,000 micro-units equal one unit of the currency.
    *
    * For example, if price is "€7.99", price_amount_micros is 7,990,000. This value represents
    * the localized, rounded price for a particular currency.
    */
    UPROPERTY(BlueprintReadOnly)
    int AmountMicros;

    /**
    * Returns ISO 4217 currency code for price and original price.
    *
    * For example, if price is specified in British pounds sterling, price_currency_code is "GBP".
    * If currency code cannot be determined, currency symbol is returned.
    */
    UPROPERTY(BlueprintReadOnly)
    FString CurrencyCode;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    //static FPrice FromRCPrice(RCPrice* price);
#endif
};



/**
 *
 */
UENUM()
enum class /*INAPPPERCHASE_API*/ ERecurrenceMode : uint8
{
    /**
    * Pricing phase repeats infinitely until cancellation
    */
    INFINITE_RECURRING = 1,
    /**
    * Pricing phase repeats for a fixed number of billing periods
    */
    FINITE_RECURRING = 2,
    /**
    * Pricing phase does not repeat
    */
    NON_RECURRING = 3,
    UNKNOWN = 4,
};



/**
 *
 */
UENUM()
enum class /*INAPPPERCHASE_API*/ EOfferPaymentMode : uint8
{
    /**
    * Subscribers don't pay until the specified period ends
    */
    FREE_TRIAL = 0,
    /**
    * Subscribers pay up front for a specified period
    */
    SINGLE_PAYMENT = 1,
    /**
    * Subscribers pay a discounted amount for a specified number of periods
    */
    DISCOUNTED_RECURRING_PAYMENT = 2,
    UNKNOWN = 3,
};
/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FPricingPhase
{
    GENERATED_USTRUCT_BODY()
    /**
 * Billing period for which the FPricingPhase applies
 */
    UPROPERTY(BlueprintReadOnly)
    FPeriod BillingPeriod;

    /**
    * Recurrence mode of the FPricingPhase
    */
    UPROPERTY(BlueprintReadOnly)
    ERecurrenceMode RecurrenceMode;

    /**
    * Number of cycles for which the pricing phase applies.
    * Null for infiniteRecurring or finiteRecurring recurrence modes.
    */
    UPROPERTY(BlueprintReadOnly)
    int BillingCycleCount;

    /**
    * Price of the FPricingPhase
    */
    UPROPERTY(BlueprintReadOnly)
    FPrice Price;

    /**
    * Indicates how the pricing phase is charged for finiteRecurring pricing phases
    */
    UPROPERTY(BlueprintReadOnly)
    EOfferPaymentMode OfferPaymentMode;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    //static FPricingPhase FromRCPricingPhase(RCPricingPhase* pricingPhase);
#endif
};

/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FSubscriptionOption
{
    GENERATED_USTRUCT_BODY()
    /**
 * Identifier of the subscription option
 * If this SubscriptionOption represents a base plan, this will be the basePlanId.
 * If it represents an offer, it will be {basePlanId}:{offerId}
 */
    UPROPERTY(BlueprintReadOnly)
    FString Id;

    /**
     * Identifier of the StoreProduct associated with this SubscriptionOption
     * This will be {subId}:{basePlanId}
     */
    UPROPERTY(BlueprintReadOnly)
    FString StoreProductId;

    /**
     * Identifer of the subscription associated with this SubscriptionOption
     * This will be {subId}
     */
    UPROPERTY(BlueprintReadOnly)
    FString ProductId;

    /**
     * Pricing phases defining a user's payment plan for the product over time.
     */
    UPROPERTY(BlueprintReadOnly)
    TArray<FPricingPhase> PricingPhases;

    /**
     * Tags defined on the base plan or offer. Empty for Amazon.
     */
    UPROPERTY(BlueprintReadOnly)
    TArray<FString> Tags;

    /**
     * True if this SubscriptionOption represents a subscription base plan (rather than an offer).
     */
    UPROPERTY(BlueprintReadOnly)
    bool IsBasePlan;

    /**
     * The subscription period of fullPricePhase (after free and intro trials).
     */
    UPROPERTY(BlueprintReadOnly)
    FPeriod BillingPeriod;

    /**
     * True if the subscription is pre-paid.
     */
    UPROPERTY(BlueprintReadOnly)
    bool IsPrepaid;

    /**
     * The full price FPricingPhase of the subscription.
     * Looks for the last price phase of the SubscriptionOption.
     */
    UPROPERTY(BlueprintReadOnly)
    FPricingPhase FullPricePhase;

    /**
     * The free trial FPricingPhase of the subscription.
     * Looks for the first pricing phase of the SubscriptionOption where amountMicros is 0.
     * There can be a freeTrialPhase and an introductoryPhase in the same SubscriptionOption.
     */
    UPROPERTY(BlueprintReadOnly)
    FPricingPhase FreePhase;

    /**
     * The intro trial FPricingPhase of the subscription.
     * Looks for the first pricing phase of the SubscriptionOption where amountMicros is greater than 0.
     * There can be a freeTrialPhase and an introductoryPhase in the same SubscriptionOption.
     */
    UPROPERTY(BlueprintReadOnly)
    FPricingPhase IntroPhase;

    UPROPERTY(BlueprintReadOnly)
    FPresentedOfferingContext PresentedOfferingContext;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    //static FSubscriptionOption FromRCSubscriptionOption(RCSubscriptionOption* subscriptionOption);
#endif
};
/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FStoreProduct
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(BlueprintReadOnly)
    FString Title;
    UPROPERTY(BlueprintReadOnly)
    FString Identifier;
    UPROPERTY(BlueprintReadOnly)
    FString Description;
    UPROPERTY(BlueprintReadOnly)
    float Price;
    UPROPERTY(BlueprintReadOnly)
    FString PriceFString;
    UPROPERTY(BlueprintReadOnly)
    FString CurrencyCode;
    UPROPERTY(BlueprintReadOnly)
    FIntroductoryPrice IntroductoryPrice;
    UPROPERTY(BlueprintReadOnly)
    EProductCategory ProductCategory;
    UPROPERTY(BlueprintReadOnly)
    FSubscriptionOption DefaultOption;
    UPROPERTY(BlueprintReadOnly)
    TArray<FSubscriptionOption> SubscriptionOptions;
    UPROPERTY(BlueprintReadOnly)
    FPresentedOfferingContext PresentedOfferingContext;
    /// <summary>
    /// Collection of iOS promotional offers for a product. Null for Android.
    /// </summary>
    /// <returns></returns>
    UPROPERTY(BlueprintReadOnly)
    TArray <FDiscount> Discounts;

    /// <summary>
    /// Subscription period, specified in ISO 8601 format. For example,
    /// P1W equates to one week, P1M equates to one month,
    /// P3M equates to three months, P6M equates to six months,
    /// and P1Y equates to one year.
    /// Note: Not available for Amazon.
    /// </summary>
    /// <returns></returns>
    UPROPERTY(BlueprintReadOnly)
    FString SubscriptionPeriod;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FStoreProduct FromRCStoreProduct(RCStoreProduct* product);
#endif
};

UENUM()
enum class EPackageType : int8
{
    RCPackageTypeUnknown = -2,
    RCPackageTypeCustom = -1,
    RCPackageTypeLifetime = 0,
    RCPackageTypeAnnual = 1,
    RCPackageTypeSixMonth = 2,
    RCPackageTypeThreeMonth = 3,
    RCPackageTypeTwoMonth = 4,
    RCPackageTypeMonthly = 5,
    RCPackageTypeWeekly = 6,
};


/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FRCPackage
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Identifier;
    UPROPERTY(BlueprintReadOnly)
    EPackageType PackageType;
    UPROPERTY(BlueprintReadOnly)
    FStoreProduct StoreProduct;
    UPROPERTY(BlueprintReadOnly)
    FPresentedOfferingContext PresentedOfferingContext;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FRCPackage FromRCPackage(RCPackage* package);
#endif
};

/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FOffering
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Identifier;
    UPROPERTY(BlueprintReadOnly)
    FString ServerDescription;
    UPROPERTY(BlueprintReadOnly)
    TArray<FRCPackage> AvailablePackages;
    UPROPERTY(BlueprintReadOnly)
    TMap<FString, UObject*> Metadata;
    UPROPERTY(BlueprintReadOnly)
    FRCPackage Lifetime;
    UPROPERTY(BlueprintReadOnly)
    FRCPackage Annual;
    UPROPERTY(BlueprintReadOnly)
    FRCPackage SixMonth;
    UPROPERTY(BlueprintReadOnly)
    FRCPackage ThreeMonth;
    UPROPERTY(BlueprintReadOnly)
    FRCPackage TwoMonth;
    UPROPERTY(BlueprintReadOnly)
    FRCPackage Monthly;
    UPROPERTY(BlueprintReadOnly)
    FRCPackage Weekly;

#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FOffering FromRCOffering(RCOffering* offering);
#endif 
};


/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FOfferings
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(BlueprintReadOnly)
    TMap<FString, FOffering> All;
    UPROPERTY(BlueprintReadOnly)
    FOffering Current;

#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FOfferings FromRCOfferings(RCOfferings* offerings);
#endif 
};

UENUM()
enum class EVerificationResult : uint8
{
    /// <summary>
    /// No verification was done. This value is returned when verification is not enabled in PurchasesConfiguration
    /// </summary>
    NotRequested,

    /// <summary>
    /// Verification with our server was performed successfully.
    /// </summary>
    Verified,

    /// <summary>
    /// Verification failed, possibly due to a MiTM attack.
    /// </summary>
    Failed,

    /// <summary>
    /// Verification was performed on device.
    /// </summary>
    VerifiedOnDevice,
};

USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FEntitlementInfo
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Identifier;
    UPROPERTY(BlueprintReadOnly)
    bool IsActive;
    UPROPERTY(BlueprintReadOnly)
    bool WillRenew;
    UPROPERTY(BlueprintReadOnly)
    int PeriodType;
    UPROPERTY(BlueprintReadOnly)
    FDateTime LatestPurchaseDate;
    UPROPERTY(BlueprintReadOnly)
    FDateTime OriginalPurchaseDate;
    UPROPERTY(BlueprintReadOnly)
    FDateTime  ExpirationDate;
    UPROPERTY(BlueprintReadOnly)
    int Store;
    UPROPERTY(BlueprintReadOnly)
    FString ProductIdentifier;
    UPROPERTY(BlueprintReadOnly)
    bool IsSandbox;
    UPROPERTY(BlueprintReadOnly)
    FDateTime  UnsubscribeDetectedAt;
    UPROPERTY(BlueprintReadOnly)
    FDateTime  BillingIssueDetectedAt;
    UPROPERTY(BlueprintReadOnly)
    EVerificationResult Verification;

#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FEntitlementInfo FromRCEntitlementInfo(RCEntitlementInfo* entitlementInfo);
#endif
};


USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FEntitlementInfos
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(BlueprintReadOnly)
    TMap<FString, FEntitlementInfo> All;
    UPROPERTY(BlueprintReadOnly)
    TMap<FString, FEntitlementInfo> Active;
    UPROPERTY(BlueprintReadOnly)
    EVerificationResult Verification;
    UPROPERTY(BlueprintReadOnly)
    FString Description;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FEntitlementInfos FromRCEntitlementInfos(RCEntitlementInfos* entitlementInfos);
#endif
};

/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FStoreTransaction
{
    GENERATED_USTRUCT_BODY()
    /**
     * <summary>
     * Id associated with the transaction in RevenueCat.
     * </summary>
     */
    UPROPERTY(BlueprintReadOnly)
    FString TransactionIdentifier;
    /**
     * <summary>
     * Product Id associated with the transaction.
     * </summary>
     */
    UPROPERTY(BlueprintReadOnly)
    FString ProductIdentifier;
    /**
     * <summary>
     * Purchase date of the transaction in UTC, be sure to compare them with DateTime.UtcNow
     * </summary>
     */
    UPROPERTY(BlueprintReadOnly)
    FDateTime PurchaseDate;

#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FStoreTransaction FromRCFStoreTransaction(RCStoreTransaction* storeTransaction);
#endif
};
/**
 *
 */
USTRUCT(BlueprintType)
struct INAPPPERCHASE_API FCustomerInfo
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(BlueprintReadOnly)
    FEntitlementInfos Entitlements;
    UPROPERTY(BlueprintReadOnly)
    TArray<FString> ActiveSubscriptions;
    UPROPERTY(BlueprintReadOnly)
    TArray<FString> AllPurchasedProductIdentifiers;
    UPROPERTY(BlueprintReadOnly)
    FDateTime  LatestExpirationDate;
    UPROPERTY(BlueprintReadOnly)
    FDateTime FirstSeen;
    UPROPERTY(BlueprintReadOnly)
    FString OriginalAppUserId;
    UPROPERTY(BlueprintReadOnly)
    FDateTime RequestDate;
    UPROPERTY(BlueprintReadOnly)
    FDateTime  OriginalPurchaseDate;
    UPROPERTY(BlueprintReadOnly)
    TMap<FString, FDateTime> AllExpirationDates;
    UPROPERTY(BlueprintReadOnly)
    TMap<FString, FDateTime> AllPurchaseDates;
    UPROPERTY(BlueprintReadOnly)
    FString OriginalApplicationVersion;
    UPROPERTY(BlueprintReadOnly)
    FString ManagementURL;
    UPROPERTY(BlueprintReadOnly)
    TArray<FStoreTransaction> NonSubscriptionTransactions;
#if PLATFORM_VISIONOS || PLATFORM_IOS
    static FCustomerInfo FromRCCustomerInfo(RCCustomerInfo * customerInfo);
#endif
};
