
#include "TileActions.h"

#include "Tile.h"
/*
 * Code edited from a tutorial on how to create custom asset types for Unreal Engine 5
 * Author: JanKXSKI
 * Link: https://dev.epicgames.com/community/learning/tutorials/vyKB/unreal-engine-creating-a-custom-asset-type-with-its-own-editor-in-c
 * Date Accessed: 04/04/2024
 */

UClass* FTileActions::GetSupportedClass() const
{
	return UTile::StaticClass();
}

FText FTileActions::GetName() const
{
	return INVTEXT("Tile");
}

FColor FTileActions::GetTypeColor() const
{
	return FColor::Blue;
}

uint32 FTileActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}
//End of tutorial code




