// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.generated.h"

class AWFCManager;

USTRUCT(BlueprintType)
struct FCell
{
	GENERATED_BODY()

public:
	FIntPoint GridPos{ 0, 0 };
	bool bIsCollapsed{ false };

	float Size{ 0.0f };
	float GroundOffset{ 0.0f };

	TArray< uint8 > WaveFunction;
	TArray< float > WFWeights;
	AWFCManager* Grid{ nullptr };

	FCell() {}
	FVector GetWorldPos() const;
	FIntPoint GetGridPos() const { return GridPos; }
	void SetWeight(uint8 TileID, float Weight);
	bool IsCollapsed() const { return bIsCollapsed; }
	float GetWeight(uint8 TileID) const { return WFWeights[ TileID ]; }
	bool IsCell(uint8 TileID) const;

	int GetEntropy() const;
};

