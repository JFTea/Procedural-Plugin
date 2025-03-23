// Copyright (c) 2024 Joshua Tunstall. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "TileSet.generated.h"

/**
 * 
 */

UCLASS()
class PROCEDURALGENERATION_API UTileSet : public UObject
{
	GENERATED_BODY()

public:
	UTileSet();

	// The name of the tileset
	UPROPERTY(EditAnywhere)
	FString TileSetName = GetName();

	// The individual tiles that make up the tile set
	UPROPERTY(EditAnywhere)
	TArray<UTile*> Tiles;

	/*
	 * Being able to clamp the minimum values for the UPROPERTY variables was inspired by the code found through this link
	 * Author: Grogger
	 * Link: https://forums.unrealengine.com/t/uproperty-min-max-values/312957
	 * Date accessed: 23/04/2024
	 */
	// The tile size of each individual object component
	UPROPERTY(EditAnywhere, meta=(ClampMin = "1"))
	FVector TileSize = FVector(1,1,1);
};


