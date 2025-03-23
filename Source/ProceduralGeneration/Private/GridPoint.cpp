// Copyright (c) 2024 Joshua Tunstall. All right reserved.
#include "GridPoint.h"

FGridPoint::FGridPoint(): GridTile(nullptr)
{
}

FGridPoint::FGridPoint(FTransform Position, UTile* InitialTile)
{
	GridPosition = Position;
	GridTile = InitialTile;
	GridTile->TileType = InitialTile->TileType;
	GridTile->XAxisTiles = InitialTile->XAxisTiles;
	GridTile->NegativeXAxisTiles = InitialTile->NegativeXAxisTiles;
	GridTile->YAxisTiles = InitialTile->YAxisTiles;
	GridTile->NegativeYAxisTiles = InitialTile->NegativeYAxisTiles;
	GridTile->ZAxisTiles = InitialTile->ZAxisTiles;
	GridTile->NegativeZAxisTiles = InitialTile->NegativeZAxisTiles;
}
