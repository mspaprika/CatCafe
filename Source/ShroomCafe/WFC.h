#pragma once 


#include "WFCManager.h"
#include <unordered_map>
#include "Math/Vector.h"
#include <functional>



class AWFCGrid;
struct FCell;
struct FTileData;
enum class ETileType : uint8;


namespace WFCAlgorithm
{
	void PropagateConstraints(FCell* Cell);
	void CollapseCell(FCell* Cell);
	void GenerateWaveFunction(TArray< FTileData >& Tiles);

	// to be used for: 
	// constraint propagation and weight accumulation
	int SweepLayer
	(
		AWFCGrid* Grid, 
		FCell* Cell, 
		uint8 TileID, 
		int32 Layer,
		std::function< int(FCell* Cell, uint8 TileID) >Func
	);

	

	// to bind std::function to a function (before pasing it ) 
	// auto BoundFunc = std::bind(&MyClass::MyMemberFunction, &Obj, std::placeholders::_1);
	// or, use lambda instead of free function - no binding needed then
}

namespace WFCWeightRules
{
	// IN current Path cell, OUT next Path cell (to be collapsed)
	FCell* PathRule(FCell* CurrentCell, TArray< FCell* >& NextCells);

	// Other rules
	float TreeRule(FCell* Cell);
	float BushRule(FCell* Cell);
	float GrassRule(FCell* Cell);
	float PineRule(FCell* Cell);
	float FernRule(FCell* Cell);
	float FlowerRule(FCell* Cell);
}

namespace WFCWeightUtils
{
	bool bAgainstOdds{ false };
	void AddRandomWeight(float& weight, float min, float max);
	int GetHighestWeightID(const TArray< float >& weights);

	float AccumulateWeights(AWFCGrid* Grid, FCell* Cell, uint8 TileID, int Layer);
	float AccumulateWeightsOptimised(AWFCGrid* Grid, FCell* Cell, uint8 TileID, int Layer);
}

namespace WFCData
{
	inline TArray< float >PathDistanceWeights
	{
		-0.2f, -0.4f, -0.6f, -0.2f
	};


	inline std::unordered_map<ETileType, float> TileRarity
	{
		{ ETileType::Tree, 0.8f },
		{ ETileType::Grass, 1.0f },
		{ ETileType::Bush, 0.5f },
	};

	inline TArray< FIntPoint > HutPositions
	{
		FIntPoint(24, 74), // Left
		FIntPoint(74, 24), // Bottom
		FIntPoint(124, 74), // Right
		FIntPoint(74, 124), // Top
	};

	//TArray<std::unordered_map< ETileType, float >>SecondLayerWeights
	inline TArray< TArray< FIntPoint > >PathCoords
	{
		{ FIntPoint(48, 74), HutPositions[ 0 ] }, //  Hut0
		{ FIntPoint(74, 48), HutPositions[ 1 ] }, //  Hut2
		{ FIntPoint(98, 74), HutPositions[ 2 ] }, //  Hut3
		{ FIntPoint(74, 98), HutPositions[ 3 ] }, //  Hut4

		{ FIntPoint(0, 30), HutPositions[ 0 ] }, // first corner BL
		{ FIntPoint(0, 0), FIntPoint(49, 49) },
		{ FIntPoint(30, 0), HutPositions[ 1 ] },

		{ FIntPoint(120, 0), HutPositions[ 1 ] }, // second corner BR
		{ FIntPoint(149, 0), FIntPoint(99, 49) },
		{ FIntPoint(149, 30), HutPositions[ 2 ] },

		{ FIntPoint(120, 149), HutPositions[ 3 ] }, // third corner TR
		{ FIntPoint(149, 149), FIntPoint(99, 99) },
		{ FIntPoint(149, 120), HutPositions[ 2 ] },

		{ FIntPoint(30, 149), HutPositions[ 3 ] }, // fourth corner TL
		{ FIntPoint(0, 149), FIntPoint(49, 99) },
		{ FIntPoint(0, 120), HutPositions[ 0 ] },

		{ FIntPoint(0, 30), FIntPoint(49, 49) },
		{ FIntPoint(30, 0), FIntPoint(49, 49) },

		{ FIntPoint(120, 0), FIntPoint(99, 49) },
		{ FIntPoint(149, 30), FIntPoint(99, 49) },

		{ FIntPoint(120, 149), FIntPoint(99, 99) },
		{ FIntPoint(149, 120), FIntPoint(99, 99) },

		{ FIntPoint(30, 149), FIntPoint(49, 99) },
		{ FIntPoint(0, 120), FIntPoint(49, 99) },
	};
}


