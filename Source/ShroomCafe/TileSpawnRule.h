// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class ATile;
struct FTileData;

class SHROOMCAFE_API TileSpawnRule
{
public:
	TileSpawnRule();
	~TileSpawnRule();

	void SetCapsule(ATile* Tile, int TileID);
	void SetMesh(ATile* Tile, FTileData* Data, int TileID);

private:
	int GetObjectCount(int TileID);
	float GetScale(int TileID);
};
