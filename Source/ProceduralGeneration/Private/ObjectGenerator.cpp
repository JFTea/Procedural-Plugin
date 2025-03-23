// Copyright (c) 2024 Joshua Tunstall. All right reserved.


#include "ObjectGenerator.h"

// Sets default values
AObjectGenerator::AObjectGenerator(): GenericTile(nullptr), TileSet(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*
	 * Being able to load the generic tile into the object can be found from this link
	 * Author: Arty-McLabin
	 * Link: https://forums.unrealengine.com/t/fobjectfinder-vs-loadobject/420207
	 * Date accessed: 27/04/2024
	 */
	// Loads the generic tile from the plugin content folder
	GenericTile = ConstructorHelpers::FObjectFinder<UTile>(TEXT("/Script/ProceduralGeneration.Tile'/ProceduralGeneration/GenericTile.GenericTile'")).Object;
}

// Called when the game starts or when spawned
void AObjectGenerator::BeginPlay()
{
	Super::BeginPlay();

	if(RunAtStart)
	{
		GenerateObject();
	}
}

// Called every frame
void AObjectGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObjectGenerator::GenerateObject()
{
	// Checks to see if there is an active tile set
	if(TileSet == nullptr)
	{
		// Displays debug message if there is no active tile set
		GEngine->AddOnScreenDebugMessage(INDEX_NONE,5, FColor::Red,"No tile set selected");
		return;
	}

	// Checks to see if the generic tile has been correctly loaded
	if(GenericTile == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE,5, FColor::Red,"No generic tile assigned");
		return;
	}
	
	Grid.Empty();
	SimulationGridOrder.Empty();

	// Sets up the generic tile adjacency programatically
	GenericTile->XAxisTiles = TileSet->Tiles;
	GenericTile->NegativeXAxisTiles = TileSet->Tiles;
	GenericTile->YAxisTiles = TileSet->Tiles;
	GenericTile->NegativeYAxisTiles = TileSet->Tiles;
	GenericTile->ZAxisTiles = TileSet->Tiles;
	GenericTile->NegativeZAxisTiles = TileSet->Tiles;
	
	CreateGrid();
}

void AObjectGenerator::CreateGrid()
{
	const FGridPoint StartingPoint = FGridPoint(GetActorTransform(), nullptr);
	// Creates the X axis grid points
	for (double i = -MaxObjectBounds.X/2 + 1; i < MaxObjectBounds.X/2; i++)
	{
		FTransform NewTransform = FTransform();
		const double NewLocationX = StartingPoint.GridPosition.GetLocation().X + TileSet->TileSize.X * i;

		// Creates the Y axis grid points
		for (int j = -MaxObjectBounds.Y/2; j < MaxObjectBounds.Y/2; j++)
		{
			const double NewLocationY = StartingPoint.GridPosition.GetLocation().Y + TileSet->TileSize.Y * j;

			// Creates the Z axis grid points
			for (int k = 0; k < MaxObjectBounds.Z; k++)
			{
				const double NewLocationZ = StartingPoint.GridPosition.GetLocation().Z + TileSet->TileSize.Z * FMath::Abs(k);
				NewTransform.SetLocation(FVector(NewLocationX, NewLocationY, NewLocationZ));
				
				FGridPoint NextPoint = FGridPoint(NewTransform, GenericTile);
				NextPoint.PotentialTiles = TileSet->Tiles;
				
				Grid.Add(NextPoint);

				/*
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				GetWorld()->SpawnActor<AActor>(NextPoint.GridTile->TileModel, NextPoint.GridPosition, SpawnParameters);
				*/
				
			}
		}
	}
	// Chooses a random tile to be the starting tile for this generation
	int32 InitialTileIndex = 0;
	while (Grid[InitialTileIndex].GridTile == nullptr || Grid[InitialTileIndex].GridTile->TileType == ETypeOfTile::Blank)
	{
		const int32 StartingTileNum = FMath::RandRange(0,TileSet->Tiles.Num() - 1);
		Grid[InitialTileIndex].GridTile = TileSet->Tiles[StartingTileNum];
	}
	
	GetAdjacentTiles();
	PopulateGrid();
}

void AObjectGenerator::PopulateGrid()
{
	// The spawn parameters for the tile objects
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Boolean checks to see if a tile was added in a loop
	bool AddedTile = true;

	AActor* InitialActor = nullptr;

	// While tiles are spawned the algorithm keeps looping
	while (AddedTile)
	{
		AddedTile = false;

		// The array containing all possible tiles that the current analysed tile can be
		TArray<UTile*> NewTileOptions = TArray<UTile*>();

		// The array containing the tiles that have to be used
		TArray<UTile*> FinalTileOptions = TArray<UTile*>();
	
		for (int i = 0; i < Grid.Num(); i++)
		{
			// Resets the arrays per loop
			NewTileOptions.Empty();
			FinalTileOptions.Empty();

			// Checks to see if the current tile is a blank tile, if it isn't then the model for that tile is spawned
			if(Grid[i].GridTile->TileType == Blank)
			{
				if(Grid[i].AdjacentXTile != nullptr)
				{
					if(Grid[i].AdjacentXTile->GridTile != nullptr)
					{
						// Checks to see if the adjacent tile on the X axis has valid neighbouring tiles
						if(!Grid[i].AdjacentXTile->GridTile->XAxisTiles.IsEmpty())
						{
							// Adds the valid tiles to the tile options
							for (int k = 0; k < Grid[i].AdjacentXTile->GridTile->XAxisTiles.Num(); k++)
							{
								NewTileOptions.Add(Grid[i].AdjacentXTile->GridTile->XAxisTiles[k]);
							}
						}
					}
				}

				if(Grid[i].AdjacentNegativeXTile != nullptr)
				{
					if(Grid[i].AdjacentNegativeXTile->GridTile != nullptr)
					{
						// Checks to see if the adjacent tile on the negative X axis has valid neighbouring tiles
						if(!Grid[i].AdjacentNegativeXTile->GridTile->NegativeXAxisTiles.IsEmpty())
						{
							// Adds the valid tiles to the tile options
							for (int k = 0; k < Grid[i].AdjacentNegativeXTile->GridTile->NegativeXAxisTiles.Num(); k++)
							{
								NewTileOptions.Add(Grid[i].AdjacentNegativeXTile->GridTile->NegativeXAxisTiles[k]);
							}
						}
					}
				}

				if(Grid[i].AdjacentYTile != nullptr)
				{
					if(Grid[i].AdjacentYTile->GridTile != nullptr)
					{
						// Checks to see if the adjacent tile on the Y axis has valid neighbouring tiles
						if(!Grid[i].AdjacentYTile->GridTile->YAxisTiles.IsEmpty())
						{
							// Adds the valid tiles to the tile options
							for (int k = 0; k < Grid[i].AdjacentYTile->GridTile->YAxisTiles.Num(); k++)
							{
								NewTileOptions.Add(Grid[i].AdjacentYTile->GridTile->YAxisTiles[k]);
							}
						}
					}
				}

				if(Grid[i].AdjacentNegativeYTile != nullptr)
				{
					if(Grid[i].AdjacentNegativeYTile->GridTile != nullptr)
					{
						// Checks to see if the adjacent tile on the negative Y axis has valid neighbouring tiles
						if(!Grid[i].AdjacentNegativeYTile->GridTile->NegativeYAxisTiles.IsEmpty())
						{
							// Adds the valid tiles to the tile options
							for (int k = 0; k < Grid[i].AdjacentNegativeYTile->GridTile->NegativeYAxisTiles.Num(); k++)
							{
								NewTileOptions.Add(Grid[i].AdjacentNegativeYTile->GridTile->NegativeYAxisTiles[k]);
							}
						}
					}
				}

				if(Grid[i].AdjacentZTile != nullptr)
				{
					if(Grid[i].AdjacentZTile->GridTile != nullptr)
					{
						// Checks to see if the adjacent tile on the Z axis has valid neighbouring tiles
						if(!Grid[i].AdjacentZTile->GridTile->ZAxisTiles.IsEmpty())
						{
							// Adds the valid tiles to the tile options
							for (int k = 0; k < Grid[i].AdjacentZTile->GridTile->ZAxisTiles.Num(); k++)
							{
								NewTileOptions.Add(Grid[i].AdjacentZTile->GridTile->ZAxisTiles[k]);
							}
						}
					}
				}

				if(Grid[i].AdjacentNegativeZTile != nullptr)
				{
					if(Grid[i].AdjacentNegativeZTile->GridTile != nullptr)
					{
						// Checks to see if the adjacent tile on the negative Z axis has valid neighbouring tiles
						if(!Grid[i].AdjacentNegativeZTile->GridTile->NegativeZAxisTiles.IsEmpty())
						{
							// Adds the valid tiles to the tile options
							for (int k = 0; k < Grid[i].AdjacentNegativeZTile->GridTile->NegativeZAxisTiles.Num(); k++)
							{
								NewTileOptions.Add(Grid[i].AdjacentNegativeZTile->GridTile->NegativeZAxisTiles[k]);
							}
						}
					}
				}
				
				for (UTile* TileOption : NewTileOptions)
				{
					// Adds up the amount of times an option appears for a tile
					int NumOfElements = 0;
					for (UTile* ComparisonTile : NewTileOptions)
					{
						if(TileOption == ComparisonTile)
						{
							NumOfElements++;
						}
					}

					// Checks if the tile option is allowed by each of the adjacent tiles
					// Adds the option to the FinalTileOptions if this is true
					if(NumOfElements == Grid[i].AdjacentCount && !FinalTileOptions.Contains(TileOption))
					{
						FinalTileOptions.Add(TileOption);
					}
				}

				// Sets the potential tiles of the grid - this can be empty if the grid has no options
				Grid[i].PotentialTiles = FinalTileOptions;

				/*if (Grid[i].PotentialTiles.Num() == 1)
				{
					Grid[i].GridTile = FinalTileOptions.Pop();

					if(Grid[i].GridTile->TileType == Blank)
					{
						Grid[i].HasSpawned = true;
						AddedTile = true;
					}
					else if(Grid[i].GridTile->TileModel != nullptr)
					{
						GetWorld()->SpawnActor<AActor>(Grid[i].GridTile->TileModel, Grid[i].GridPosition, SpawnParameters);
						Grid[i].HasSpawned = true;
						AddedTile = true;
					}
				}*/
			}
			else
			{
				if(Grid[i].GridTile->TileModel != nullptr && !Grid[i].HasSpawned)
				{
					if(Grid[i].GridTile->TileType == Model)
					{
						AActor* TempActor =GetWorld()->SpawnActor<AActor>(Grid[i].GridTile->TileModel, Grid[i].GridPosition, SpawnParameters);
						InitialActor = TempActor;
						SimulationGridOrder.Add(TempActor);
					}
					Grid[i].HasSpawned = true;
					AddedTile = true;
				}
			}
		}

		FGridPoint* PointWithLowestEntropy = nullptr;

		// Finds the point of the grid with the lowest amount of tile options (entropy)
		for (int i = 0; i < Grid.Num(); i++)
		{
			// Checks to see if the tile has spawned or if the tile has no potential options or if the tile has every possible option available
			if(!Grid[i].HasSpawned && !Grid[i].PotentialTiles.IsEmpty() && Grid[i].PotentialTiles.Num() != Grid[i].AdjacentCount)
			{
				if(PointWithLowestEntropy != nullptr)
				{
					// If the latest grid has lower entropy than the current point then it replaces the current point
					if(Grid[i].PotentialTiles.Num() < PointWithLowestEntropy->PotentialTiles.Num() && Grid[i].PotentialTiles.Num() > 0)
					{
						PointWithLowestEntropy = &Grid[i];
					}
				}
				else
				{
					// Sets the Point to the first grid tile in the array
					PointWithLowestEntropy = &Grid[i];
				}

				// Breaks the loop if the entropy is the lowest value possible without being empty
				if(PointWithLowestEntropy->PotentialTiles.Num() == 1)
				{
					break;
				}
			}
		}
		
		if(PointWithLowestEntropy != nullptr)
		{
			// Spawns the point with the lowest entropy
			UTile* SpawnTile;

			// If tile weighting is being used the method of spawning for multiple options uses weights
			if(UseWeighting)
			{
				TArray<UTile*> TilesWithWeight;
				for (UTile* Tile : PointWithLowestEntropy->PotentialTiles)
				{
					for (int i = 0; i < Tile->TileWeight; i++)
					{
						TilesWithWeight.Add(Tile);
					}
				}

				SpawnTile = TilesWithWeight[FMath::RandRange(0,TilesWithWeight.Num() - 1)];
			}
			else
			{
				// If tile weighting isn't used then the tile chosen to spawn is chosen at random
				SpawnTile = PointWithLowestEntropy->PotentialTiles[FMath::RandRange(0, PointWithLowestEntropy->PotentialTiles.Num() - 1)];
			}

			// Asigns the Spawn tile to the tile point
			PointWithLowestEntropy->GridTile = SpawnTile;

			// If the tile type is model the tile model is spawned
			if(PointWithLowestEntropy->GridTile->TileType == Model)
			{
				// Converts the rotation of the tile to a quaternion
				UE::Math::TQuat<double> TileRotation = PointWithLowestEntropy->GridTile->RotationOfTile.ToOrientationQuat();
				PointWithLowestEntropy->GridPosition.SetRotation(TileRotation);

				// Spawns the tile model
				AActor* TempActor = GetWorld()->SpawnActor<AActor>(PointWithLowestEntropy->GridTile->TileModel, PointWithLowestEntropy->GridPosition, SpawnParameters);

				// Adds the tile actor to the array needed for the visual simulation to take place
				SimulationGridOrder.Add(TempActor);

				// Attaches the actor to the first spawned tile
				TempActor->AttachToActor(InitialActor, FAttachmentTransformRules::KeepWorldTransform);
			}
			PointWithLowestEntropy->HasSpawned = true;
			AddedTile = true;
		}
	}
}

void AObjectGenerator::GetAdjacentTiles()
{
	for (int i = 0; i < Grid.Num() - 1; i++)
	{
		// The position of the currently evaluated grid tile
		const double XPosition = Grid[i].GridPosition.GetLocation().X;
		const double YPosition = Grid[i].GridPosition.GetLocation().Y;
		const double ZPosition = Grid[i].GridPosition.GetLocation().Z;

		// This iterates through the grid checking for tile adjacency
		for (int j = 0; j < Grid.Num() - 1; j++)
		{
			// The position of the current testing tile
			const double TestXPosition = Grid[j].GridPosition.GetLocation().X;
			const double TestYPosition = Grid[j].GridPosition.GetLocation().Y;
			const double TestZPosition = Grid[j].GridPosition.GetLocation().Z;

			// Checks to see if the testing tile is adjacent on the X axis
			if(Grid[i].AdjacentXTile == nullptr && XPosition == TestXPosition + TileSet->TileSize.X && YPosition == TestYPosition && ZPosition == TestZPosition)
			{
				Grid[i].AdjacentXTile = &Grid[j];
				Grid[i].AdjacentCount++;
			}

			// Checks to see if the testing tile is adjacent on the negative X axis
			if(Grid[i].AdjacentNegativeXTile == nullptr && XPosition == TestXPosition - TileSet->TileSize.X && YPosition == TestYPosition && ZPosition == TestZPosition)
			{
				Grid[i].AdjacentNegativeXTile = &Grid[j];
				Grid[i].AdjacentCount++;
			}

			// Checks to see if the testing tile is adjacent on the Y axis
			if(Grid[i].AdjacentYTile == nullptr && YPosition == TestYPosition + TileSet->TileSize.Y && XPosition == TestXPosition && ZPosition == TestZPosition)
			{
				Grid[i].AdjacentYTile = &Grid[j];
				Grid[i].AdjacentCount++;
			}

			// Checks to see if the testing tile is adjacent on the negative Y axis
			if(Grid[i].AdjacentNegativeYTile == nullptr && YPosition == TestYPosition - TileSet->TileSize.Y && XPosition == TestXPosition && ZPosition == TestZPosition)
			{
				Grid[i].AdjacentNegativeYTile = &Grid[j];
				Grid[i].AdjacentCount++;
			}

			// Checks to see if the testing tile is adjacent on the Z axis
			if(Grid[i].AdjacentZTile == nullptr && ZPosition == TestZPosition + TileSet->TileSize.Z && XPosition == TestXPosition && YPosition == TestYPosition)
			{
				Grid[i].AdjacentZTile = &Grid[j];
				Grid[i].AdjacentCount++;
			}

			// Checks to see if the testing tile is adjacent on the negative Z axis
			if(Grid[i].AdjacentNegativeZTile == nullptr && ZPosition == TestZPosition - TileSet->TileSize.Z && XPosition == TestXPosition && YPosition == TestYPosition)
			{
				Grid[i].AdjacentNegativeZTile = &Grid[j];
				Grid[i].AdjacentCount++;
			}

			// Checks to see if the currently evaluated tile has full adjacency and breaks the loop if so
			if(Grid[i].AdjacentCount >= 6)
			{
				break;
			}
		}
	}
}


void AObjectGenerator::AlgorithmSimulation()
{

	if(MaxObjectBounds.X * MaxObjectBounds.Y * MaxObjectBounds.Z >= 10000)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE,5, FColor::Red,"Grid too large for simulation to proceed");
		return;
	}
	
	/*
	 * Using this async method was inspired by the linked code
	 * Author: Georgy
	 * Link: https://georgy.dev/posts/async-task/
	 * Date Accessed: 23/04/2024
	 */
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
	{
		if(!SimulationGridOrder.IsEmpty())
		{
			for (AActor* Actor : SimulationGridOrder)
			{
				if(Actor != nullptr)
				{
					Actor->SetHidden(true);
					Actor->SetIsHiddenEdLayer(true);
				}
			}

			for (AActor* Actor : SimulationGridOrder)
			{
				if(Actor != nullptr)
				{
					Actor->SetHidden(false);
					Actor->SetIsHiddenEdLayer(false);
				}
				/*
				 * This method is used to delay the application showing the tile objects to be spawning over time for the simulation
				 * Author: Natsu Games
				 * Link: https://www.youtube.com/watch?v=UyloKYQpYFM&ab_channel=NatsuGames
				 * Date Accessed: 23/04/2024
				 */
				FPlatformProcess::Sleep(SimulationSpeed);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE,5, FColor::Red,"No object available to simulate");
		}
	});
}

