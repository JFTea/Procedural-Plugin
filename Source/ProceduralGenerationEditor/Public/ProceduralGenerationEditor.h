// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ObjectGeneratorActions.h"
#include "TileActions.h"
#include "TileSetActions.h"

class FProceduralGenerationEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	TSharedPtr<FTileActions> TileActions;

	TSharedPtr<FTileSetActions> TileSetActions;

	TSharedPtr<FObjectGeneratorActions> ObjectGeneratorActions;
};
