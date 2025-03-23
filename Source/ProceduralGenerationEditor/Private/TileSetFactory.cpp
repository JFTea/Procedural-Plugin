
#include "TileSetFactory.h"

#include "TileSet.h"
/*
 * Code edited from a tutorial on how to create custom asset types for Unreal Engine 5
 * Author: JanKXSKI
 * Link: https://dev.epicgames.com/community/learning/tutorials/vyKB/unreal-engine-creating-a-custom-asset-type-with-its-own-editor-in-c
 * Date Accessed: 04/04/2024
 */

UTileSetFactory::UTileSetFactory()
{
	SupportedClass = UTileSet::StaticClass();
	bCreateNew = true;
}

UObject* UTileSetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UTileSet>(InParent,InClass, InName, Flags, Context);
}
//End of tutorial code
