// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "K2Node_BaseAsyncTask.h"

#include "InAppPerchaseBlueprintSupport.generated.h"

UCLASS()
class  INAPPPERCHASEBLUEPRINTSUPPORT_API UK2Node_GetOfferings :
	public UK2Node_BaseAsyncTask
{
	GENERATED_UCLASS_BODY()
};

UCLASS()
class  INAPPPERCHASEBLUEPRINTSUPPORT_API UK2Node_Purchase :
	public UK2Node_BaseAsyncTask
{
	GENERATED_UCLASS_BODY()
};
UCLASS()
class  INAPPPERCHASEBLUEPRINTSUPPORT_API UK2Node_GetCustomerInfo :
	public UK2Node_BaseAsyncTask
{
	GENERATED_UCLASS_BODY()
};

UCLASS()
class  INAPPPERCHASEBLUEPRINTSUPPORT_API UK2Node_RestorePurchases :
	public UK2Node_BaseAsyncTask
{
	GENERATED_UCLASS_BODY()
};