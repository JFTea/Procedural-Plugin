
#include "TileSetActions.h"

#include "TileSet.h"
/*
 * Code edited from a tutorial on how to create custom asset types for Unreal Engine 5
 * Author: JanKXSKI
 * Link: https://dev.epicgames.com/community/learning/tutorials/vyKB/unreal-engine-creating-a-custom-asset-type-with-its-own-editor-in-c
 * Date Accessed: 04/04/2024
 */

UClass* FTileSetActions::GetSupportedClass() const
{
	return UTileSet::StaticClass();
}

FText FTileSetActions::GetName() const
{
	return INVTEXT("Tile Set");
}

FColor FTileSetActions::GetTypeColor() const
{
	return FColor::Emerald;
}

uint32 FTileSetActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}
//End of tutorial code



