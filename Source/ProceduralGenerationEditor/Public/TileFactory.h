
#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "TileFactory.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALGENERATIONEDITOR_API UTileFactory : public UFactory
{
	GENERATED_BODY()

public:
	/*
	* Code edited from a tutorial on how to create custom asset types for Unreal Engine 5
	* Author: JanKXSKI
	* Link: https://dev.epicgames.com/community/learning/tutorials/vyKB/unreal-engine-creating-a-custom-asset-type-with-its-own-editor-in-c
	* Date Accessed: 04/04/2024
	*/
	UTileFactory();

	UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	//End of tutorial code
};
