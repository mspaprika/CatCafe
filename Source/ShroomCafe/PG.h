#pragma once

#include "CoreMinimal.h"

class AWFCGrid;
struct FCell;



namespace ProceduralPath
{
	void Generate(AWFCGrid* Grid, FCell* Start, FCell* End, UWorld* world = nullptr);
	void GetSurroundingCells(FCell* Current, TArray< FCell* >& Next);
}

namespace ProceduralWorld
{
	void Generate(AWFCGrid* Grid, UWorld* world = nullptr);
	FCell* FindLowestEntropyCell(AWFCGrid* Grid);
}