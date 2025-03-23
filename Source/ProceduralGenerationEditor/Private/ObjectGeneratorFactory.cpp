
#include "ObjectGeneratorFactory.h"

#include "ObjectGenerator.h"

/*
 * Code edited from a tutorial on how to create custom asset types for Unreal Engine 5
 * Author: JanKXSKI
 * Link: https://dev.epicgames.com/community/learning/tutorials/vyKB/unreal-engine-creating-a-custom-asset-type-with-its-own-editor-in-c
 * Date Accessed: 04/04/2024
 */

UObjectGeneratorFactory::UObjectGeneratorFactory()
{
	SupportedClass = AObjectGenerator::StaticClass();
	bCreateNew = true;
}

UObject* UObjectGeneratorFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<AObjectGenerator>(InParent, InClass, InName, Flags,Context);
}

//End of tutorial code