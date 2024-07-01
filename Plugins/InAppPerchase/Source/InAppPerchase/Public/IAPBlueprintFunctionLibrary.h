
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IAPBlueprintFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class INAPPPERCHASE_API UIAPBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = IAP)
		static bool InitIAP(const FString& APIKey, const FString& UserId);
};
