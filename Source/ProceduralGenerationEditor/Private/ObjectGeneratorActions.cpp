
#include "ObjectGeneratorActions.h"

#include "ObjectGenerator.h"

/*
 * Code edited from a tutorial on how to create custom asset types for Unreal Engine 5
 * Author: JanKXSKI
 * Link: https://dev.epicgames.com/community/learning/tutorials/vyKB/unreal-engine-creating-a-custom-asset-type-with-its-own-editor-in-c
 * Date Accessed: 04/04/2024
 */

UClass* FObjectGeneratorActions::GetSupportedClass() const
{
	return AObjectGenerator::StaticClass();
}

FText FObjectGeneratorActions::GetName() const
{
	return INVTEXT("Object Generator");
}

FColor FObjectGeneratorActions::GetTypeColor() const
{
	return FColor::Blue;
}

uint32 FObjectGeneratorActions::GetCategories()
{
	return EAssetTypeCategories::None;
}
//End of tutorial code
