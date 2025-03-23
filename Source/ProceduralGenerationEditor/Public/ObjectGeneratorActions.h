
#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class PROCEDURALGENERATIONEDITOR_API FObjectGeneratorActions: public FAssetTypeActions_Base
{
public:
	/*
	 * Code edited from a tutorial on how to create custom asset types for Unreal Engine 5
	 * Author: JanKXSKI
	 * Link: https://dev.epicgames.com/community/learning/tutorials/vyKB/unreal-engine-creating-a-custom-asset-type-with-its-own-editor-in-c
	 * Date Accessed: 04/04/2024
	 */
	UClass* GetSupportedClass() const override;
	FText GetName() const override;
	FColor GetTypeColor() const override;
	uint32 GetCategories() override;
	// End of tutorial code
};
