// Copyright (c) 2024 Joshua Tunstall. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tile.generated.h"


/**
 * The type of the tile between having a model or being blank
 */
UENUM()
enum ETypeOfTile
{
	Model,
	Blank
};
// The class that defines a tile used for procedural generation
UCLASS()
class PROCEDURALGENERATION_API UTile : public UObject
{
	GENERATED_BODY()
public:
	UTile();
	
	// The name of the tile
	UPROPERTY(EditAnywhere)
	FString TileName = GetName();

	// Defines if the type of tile that will be spawned
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ETypeOfTile> TileType = Blank;
	
	// The model related to the tile
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TileModel;

	// The set rotation of the tile model when it is spawned
	UPROPERTY(EditAnywhere)
	FVector RotationOfTile = FVector::Zero();

	/*
	 * Being able to clamp the minimum values for the UPROPERTY variables was inspired by the code found through this link
	 * Author: Grogger
	 * Source: https://forums.unrealengine.com/t/uproperty-min-max-values/312957
	 * Date accessed: 23/04/2024
	 */
	// How likely the tile is to spawn compared to the other tile options
	UPROPERTY(EditAnywhere, meta=(ClampMin = "1", ClampMax = "9"))
	uint16 TileWeight = 1;

	// The possible tiles that can be adjacent to this tile on the X axis
	UPROPERTY(EditAnywhere, Category="Tile|Adjacents")
	TArray<UTile*> XAxisTiles;

	// The possible tiles that can be adjacent to this tile on the negative X axis
	UPROPERTY(EditAnywhere, Category="Tile|Adjacents")
	TArray<UTile*> NegativeXAxisTiles;

	// The possible tiles that can be adjacent to this tile on the Y axis
	UPROPERTY(EditAnywhere, Category="Tile|Adjacents")
	TArray<UTile*> YAxisTiles;

	// The possible tiles that can be adjacent to this tile on the negative Y axis
	UPROPERTY(EditAnywhere, Category="Tile|Adjacents")
	TArray<UTile*> NegativeYAxisTiles;

	// The possible tiles that can be adjacent to this tile on the Z axis
	UPROPERTY(EditAnywhere, Category="Tile|Adjacents")
	TArray<UTile*> ZAxisTiles;

	// The possible tiles that can be adjacent to this tile on the negative Z axis
	UPROPERTY(EditAnywhere, Category="Tile|Adjacents")
	TArray<UTile*> NegativeZAxisTiles;
};


