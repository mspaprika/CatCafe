// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"
#include "WFCManager.h"


// return the position where mesh will be spawned
FVector FCell::GetWorldPos() const 
{ 
	FVector ParentPos = Grid->GetActorLocation();

	// 2D world position for the cell
	FVector2D WorldPos = FVector2D(ParentPos.X, ParentPos.Y) + FVector2D((GridPos.X * Size) + (Size / 2), (GridPos.Y * Size) + (Size / 2));
	// add height offset for 3D position
	return FVector(WorldPos, 0);
}

void FCell::SetWeight(uint8 TileID, float Weight)
{
	if (WFWeights.Num() == 0)
		WFWeights.Init(1.0f, (int)ETileType::Max_Tiles);

	WFWeights[ TileID ] = Weight;
}

bool FCell::IsCell(uint8 TileID) const
{
	if (!bIsCollapsed) return false;
	return WaveFunction[ 0 ] == TileID;
}

int FCell::GetEntropy() const
{
	int Entropy{ 0 };
	// skip unknown and path (0, 1); path is already collapsed
	for (int i = 2; i < WFWeights.Num(); i++)
	{
		if (WFWeights[ i ] != AWFCManager::sEntropyThreshold)
			Entropy++;
	}
	return Entropy;
}
