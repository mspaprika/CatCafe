// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "Tile.h"
#include "WFCGrid.generated.h"

UENUM(BlueprintType)
enum class ETileType: uint8
{
	Unknown UMETA(DisplayName = "Unknown"),
	Path UMETA(DisplayName = "Path"),
	Tree UMETA(DisplayName = "Tree"),
	Grass UMETA(DisplayName = "Grass"),
	Bush UMETA(DisplayName = "Bush"),
	
	Max_Tiles UMETA(DisplayName = "Max_Tiles")
};


UCLASS()
class SHROOMCAFE_API AWFCGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AWFCGrid() {}
	
	AWFCGrid(int rows, int columns, TArray< FTileData >& tiles);

	TArray< FTileData >WaveFunction;

protected:
	TArray<TArray< FCell >>Cells;
	int32 GridWidth;
	int32 GridHeight;
	float Randomness;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	TArray < TArray<FCell> >& GetCells() { return Cells; }

	FCell& GetCellAtPosition(FIntPoint& pos);

	int32 GetGridWidth() const { return GridWidth; }
	int32 GetGridHeight() const { return GridHeight; }

	void SetGridWidth(int32 width) { GridWidth = width; }
	void SetGridHeight(int32 height) { GridHeight = height; }

	void SetRandomness(float randomness) { Randomness = randomness; }
	float GetRandomness() const { return Randomness; }
};
