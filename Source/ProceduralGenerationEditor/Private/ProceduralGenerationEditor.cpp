// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralGenerationEditor.h"

#define LOCTEXT_NAMESPACE "FProceduralGenerationModule"

void FProceduralGenerationEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	/*
	* The following code was taken from a tutorial on creating custom assets
	Author: JanKXSKI
	Link: https://dev.epicgames.com/community/learning/tutorials/vyKB/unreal-engine-creating-a-custom-asset-type-with-its-own-editor-in-c
	Date Accessed: 04/04/2024
	*/
	TileActions = MakeShared<FTileActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(TileActions.ToSharedRef());
	
	TileSetActions = MakeShared<FTileSetActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(TileSetActions.ToSharedRef());
	
	ObjectGeneratorActions = MakeShared<FObjectGeneratorActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(ObjectGeneratorActions.ToSharedRef());
	// End of tutorial code
}

void FProceduralGenerationEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	/*
	* The following code was taken from a tutorial on creating custom assets
	Author: JanKXSKI
	Link: https://dev.epicgames.com/community/learning/tutorials/vyKB/unreal-engine-creating-a-custom-asset-type-with-its-own-editor-in-c
	Date Accessed: 04/04/2024
	*/
	if(!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;
	
	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(TileActions.ToSharedRef());
	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(TileSetActions.ToSharedRef());
	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(ObjectGeneratorActions.ToSharedRef());
	// End of tutorial code
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FProceduralGenerationEditorModule, ProceduralGeneration)