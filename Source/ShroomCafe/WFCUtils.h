// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class ATile;
struct FCell;
class AWFCGrid;
/**
 * 
 */
class SHROOMCAFE_API WFCUtils
{
public:
	WFCUtils();
	~WFCUtils();

	static UStaticMeshComponent* GetTileMesh(FString TargetName, UWorld* World);
	static void SortCellsByDistance(FCell* Target, TArray< FCell* >& Cells);
	static bool IsPositionWithinBounds(FIntPoint* Pos, AWFCGrid* Grid);
	static FVector2D GetRandomPosition(float tileSize, float angle);

protected:
};
