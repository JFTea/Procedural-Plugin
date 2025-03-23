// Copyright (c) 2024 Joshua Tunstall. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "TileSet.h"
#include "GameFramework/Actor.h"
#include "GridPoint.h"
#include "ObjectGenerator.generated.h"

UCLASS(Blueprintable)
class PROCEDURALGENERATION_API AObjectGenerator : public AActor
{
	GENERATED_BODY()
	
	// Creates the grid needed for procedural generation
	void CreateGrid();

	// Populates the grid using the wave function collapse algorithm
	void PopulateGrid();

	// Gets the adjacent tiles for every tile in the grid
	void GetAdjacentTiles();

	// The grid where the procedural generation will take place
	TArray<FGridPoint> Grid;

	//The order which tiles are spawned to allow the user to see a graphical implementation of the algorithm
	UPROPERTY()
	TArray<AActor*> SimulationGridOrder;

	UPROPERTY()
	UTile* GenericTile;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AObjectGenerator();

	// The tile set used by this object generator
	UPROPERTY(EditAnywhere)
	UTileSet* TileSet;

	/*
	 * Being able to clamp the minimum values for the UPROPERTY variables was inspired by the code found through this link
	 * Author: Grogger
	 * Source: https://forums.unrealengine.com/t/uproperty-min-max-values/312957
	 * Date accessed: 23/04/2024
	 */
	// The bounds of where the object will be generated
	UPROPERTY(EditAnywhere, meta=(ClampMin = "1"))
	FVector MaxObjectBounds = FVector(0,0,0);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Boolean that checks if the tile weighting is active
	UPROPERTY(EditAnywhere, Category="ObjectGenerator|Extra")
	bool UseWeighting = false;

	// Check to run the generate terrain script at Start
	UPROPERTY(EditAnywhere, Category="ObjectGenerator|Extra")
	bool RunAtStart = false;

	// The function called to generate a procedural generation object
	UFUNCTION(BlueprintCallable, CallInEditor, Category= "ObjectGenerator")
	void GenerateObject();

	// Function to display the tile spawning simulation
	UFUNCTION(CallInEditor, Category= "ObjectGenerator")
	void AlgorithmSimulation();

	/*
	 * Being able to clamp the minimum values for the UPROPERTY variables was inspired by the code found through this link
	 * Author: Grogger
	 * Source: https://forums.unrealengine.com/t/uproperty-min-max-values/312957
	 * Date accessed: 23/04/2024
	 */
	// The delay in seconds between tiles being visible in the simulation
	UPROPERTY(EditInstanceOnly, meta=(ClampMin = "0"))
	float SimulationSpeed = 0.1f;
};
