// Copyright (c) 2024 Joshua Tunstall. All right reserved.
#pragma once
#include "Tile.h"
#include "GridPoint.generated.h"


// An individual point in the grid that includes its position and the Tile assigned to it
USTRUCT()
struct FGridPoint
{
	GENERATED_BODY()
	// A generic constructor
	FGridPoint();

	// The constructor for a grid tile that already has a position and tile
	FGridPoint(FTransform Position, UTile* InitialTile);

	// The X adjacent tiles
	FGridPoint* AdjacentXTile = nullptr;
	FGridPoint* AdjacentNegativeXTile = nullptr;

	// The Y adjacent tiles
	FGridPoint* AdjacentYTile = nullptr;
	FGridPoint* AdjacentNegativeYTile = nullptr;

	// The Z adjacent tiles
	FGridPoint* AdjacentZTile = nullptr;
	FGridPoint* AdjacentNegativeZTile = nullptr;

	// The amount of adjacent tiles
	int AdjacentCount = 0;

	// The world position of the grid tile
	FTransform GridPosition;

	// An array that holds all the potential tiles that could be assigned to this grid position
	UPROPERTY()
	TArray<UTile*> PotentialTiles;
	
	// The Complete Tile property that contains the models for the grid tile
	UPROPERTY()
	UTile* GridTile;

	// A boolean that checks if the grid point has spawned a tile
	bool HasSpawned = false;
};
