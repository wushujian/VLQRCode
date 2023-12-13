// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QRCodeUtils.generated.h"

/**
 * 
 */
UCLASS()
class VLQRCODE_API UQRCodeUtils : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "QRCode", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext))
	static UTexture2D* CreateQRCodeTexture(const UObject* WorldContextObject, const FString& url, int sizelevel = 3);
};
