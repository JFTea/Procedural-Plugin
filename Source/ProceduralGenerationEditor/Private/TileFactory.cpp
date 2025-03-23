
#include "TileFactory.h"

#include "Tile.h"
/*
 * Code edited from a tutorial on how to create custom asset types for Unreal Engine 5
 * Author: JanKXSKI
 * Link: https://dev.epicgames.com/community/learning/tutorials/vyKB/unreal-engine-creating-a-custom-asset-type-with-its-own-editor-in-c
 * Date Accessed: 04/04/2024
 */

UTileFactory::UTileFactory()
{
	SupportedClass = UTile::StaticClass();
	bCreateNew = true;
}

UObject* UTileFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UTile>(InParent, InClass, InName, Flags,Context);
}

//End of tutorial code