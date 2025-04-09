// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WFCGrid.h"
#include "WFCManager.generated.h"

class ATileSpawner;

UCLASS()
class SHROOMCAFE_API AWFCManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWFCManager();
	static const TCHAR* GetMeshString(uint8 TileID);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DrawDebugGrid();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// pull tiles from json later 
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void InitializeGrid();

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void GenerateGrid();

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SpawnGrid();

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void OnProceduralGeneration();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 GridWidth{ 150 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 GridHeight{ 150 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 TileSize{ 300 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float Randomness{ 0.02f };

	int32 GetGridWidth() const { return GridWidth; }
	int32 GetGridHeight() const { return GridHeight; }
	static TArray<FTileData >& GetTiles() { return sTiles; }
	AWFCGrid* GetGrid() { return Grid; }
	static const float sEntropyThreshold;
	static float sMinMeshOffset;
	static TArray< FTileData > sTiles;
	static int32 sTileSize;
	
protected:
	AWFCGrid* Grid{ nullptr };
	ATileSpawner* TileSpawner{ nullptr };
	bool bGenerated{ false };

	// height and width is swapped unintentionally, but at this point and time it's too painful to fix
	// therefore height is width and width is height
	float VerticalOffset = 0.0f;

	FIntPoint MiddlePerimeterSize{ 50, 50 };
	FIntPoint MiddlePerimeterBottomLeft{ 50, 50 };

	FIntPoint MiddlePerimeterTopRight{ 
		MiddlePerimeterBottomLeft.X + MiddlePerimeterSize.X, 
		MiddlePerimeterBottomLeft.Y + MiddlePerimeterSize.Y };

};
