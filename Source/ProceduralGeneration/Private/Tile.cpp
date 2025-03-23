// Copyright (c) 2024 Joshua Tunstall. All right reserved.

#include "Tile.h"

UTile::UTile(): TileModel(nullptr)
{
	if(TileModel != nullptr)
	{
		TileType = Model;
	}
	else
	{
		TileType = Blank;
	}
}
