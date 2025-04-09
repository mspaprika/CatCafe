#include "WFC.h"
#include "WFCManager.h"
#include "WFCUtils.h"
#include "PG.h"

using WeightMap = TArray<std::unordered_map< ETileType, float >>;

// later to be loaded into json
namespace WFCData
{
	// Weight will be adjusted for each wave function element, based on these weights

	TArray<std::unordered_map< ETileType, float >>FirstLayerWeights
	{
		{}, // Unknown Tile = 0, 
		{}, // Path Tile = 1

		{	// Tree Tile = 2 
			{ ETileType::Path, 0.3f },
			{ ETileType::Tree, 0.2f },
			{ ETileType::Grass, 0.15f },
			{ ETileType::Bush, 0.3f },
			
		},
		{	// Grass Tile = 3
			{ ETileType::Path, 0.25f },
			{ ETileType::Tree, 0.2f },
			{ ETileType::Grass, 0.1f },
			{ ETileType::Bush, 0.3f },
		},
		{	// Bush Tile = 4
			{ ETileType::Path, 0.25f },
			{ ETileType::Tree, 0.3f },
			{ ETileType::Grass, 0.3f },
			{ ETileType::Bush, 0.1f },
		}
	};

	TArray<std::unordered_map< ETileType, float >>SecondLayerWeights
	{	
		{}, // Unknown Tile = 0, 
		{}, // Path Tile = 1

		{	// Tree Tile = 2
			{ ETileType::Path, 0.3f },
			{ ETileType::Tree, 0.2f },
			{ ETileType::Grass, 0.2f },
			{ ETileType::Bush, 0.3f },
		},
		{	// Grass Tile = 3 
			{ ETileType::Path, 0.25f },
			{ ETileType::Tree, 0.2f },
			{ ETileType::Grass, 0.1f },
			{ ETileType::Bush, 0.3f },
		},
		{	// Bush Tile = 4
			{ ETileType::Path, 0.25f },
			{ ETileType::Tree, 0.3f },
			{ ETileType::Grass, 0.2f },
			{ ETileType::Bush, 0.1f },
		}
	};

	// first item is nullptr as there is no level 0
	TArray< WeightMap* > WeightMaps{ nullptr, &FirstLayerWeights, &SecondLayerWeights };
}

namespace WFCAlgorithm
{
	
	// Reduce entropy of the surrounding cells
	void PropagateConstraints(FCell* Cell)
	{
		// tile IDs correspond to positions in array, therefore no removing them happens
		// instead weight is set to -10.0f and later is ignored
		if (!Cell) return;
		uint8 TileID = Cell->WaveFunction[ 0 ];
		FTileData* CollapsedTile = &Cell->Grid->GetTiles()[ TileID ];

		auto UpdateEntropy = [&](FCell* ACell, uint8 TileID) -> int
			{
				for (int i = 0; i < ACell->WaveFunction.Num(); i++)
				{
					if (!CollapsedTile->IsAllowedNeighbor(ACell->WaveFunction[ i ]))
					{
						ACell->WFWeights[ i ] = -10.0f;
						return 1;
					}
				}
				return 0;
			};

		SweepLayer(Cell->Grid->GetGrid(), Cell, TileID, 1, UpdateEntropy);
	}

	void CollapseCell(FCell* Cell)
	{
		// Check all weights and find highest (ignore -1)
		// Collapse wave function to single tile of that weight
		// Set WaveFunction to single tile
		if (!Cell) return;

		int TileID = WFCWeightUtils::GetHighestWeightID(Cell->WFWeights);
		if (TileID == -1) return;

		Cell->WaveFunction.Empty();
		Cell->WaveFunction.Add(TileID);
		Cell->bIsCollapsed = true;
	}

	void GenerateWaveFunction(TArray< FTileData >& Tiles)
	{
		UE_LOG(LogTemp, Warning, TEXT("Creating Tiles Aleliuja 2025"));

		Tiles.Empty();

		FTileData UnknownTile((int)ETileType::Unknown, TArray<uint8>{ (int)ETileType::Bush, (int)ETileType::Grass, (int)ETileType::Tree, (int)ETileType::Path });
		UnknownTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Nimikko_WesternTown/Assets/Props/SM_Crate_03.SM_Crate_03'"));
		Tiles.Add(UnknownTile);

		FTileData PathTile((int)ETileType::Path, TArray<uint8>{ (int)ETileType::Bush, (int)ETileType::Grass, (int)ETileType::Path });
		PathTile.SetMeshString(FString("/Script/Engine.Blueprint'/Game/WFC/BP_Rock.BP_Rock'"));
		Tiles.Add(PathTile);

		FTileData TreeTile((int)ETileType::Tree, TArray<uint8>{ (int)ETileType::Bush, (int)ETileType::Grass, (int)ETileType::Tree });
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Fantastic_Village_Pack/meshes/environment/SM_ENV_TREE_village_LOD0.SM_ENV_TREE_village_LOD0'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Fantastic_Village_Pack/meshes/environment/SM_ENV_TREE_village_LOD0.SM_ENV_TREE_village_LOD0'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Common_Tree_01.SM_Common_Tree_01'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Common_Tree_02.SM_Common_Tree_02'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Common_Tree_03.SM_Common_Tree_03'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Common_Tree_04.SM_Common_Tree_04'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Common_Tree_05.SM_Common_Tree_05'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Common_Tree_06.SM_Common_Tree_06'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Common_Tree_07.SM_Common_Tree_07'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Common_Tree_08.SM_Common_Tree_08'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Common_Tree_09.SM_Common_Tree_09'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Common_Tree_10.SM_Common_Tree_10'"));
		TreeTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Common_Tree_11.SM_Common_Tree_11'"));
		Tiles.Add(TreeTile);

		FTileData GrassTile((int)ETileType::Grass, TArray<uint8>{ (int)ETileType::Bush, (int)ETileType::Grass, (int)ETileType::Tree, (int)ETileType::Path });
		GrassTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Fantastic_Village_Pack/meshes/environment/SM_ENV_PLANT_grass_village.SM_ENV_PLANT_grass_village'"));
		GrassTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Fantastic_Village_Pack/meshes/environment/SM_ENV_PLANT_grass_village.SM_ENV_PLANT_grass_village'"));
		GrassTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Fantastic_Village_Pack/meshes/environment/SM_ENV_PLANT_grass_village.SM_ENV_PLANT_grass_village'"));
		GrassTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Fantastic_Village_Pack/meshes/environment/SM_ENV_PLANT_grass_village.SM_ENV_PLANT_grass_village'"));
		GrassTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Fantastic_Village_Pack/meshes/environment/SM_ENV_PLANT_grass_village.SM_ENV_PLANT_grass_village'"));
		GrassTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/StylizedProvencal/Meshes/SM_Flower_01_c.SM_Flower_01_c'"));
		GrassTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/StylizedProvencal/Meshes/SM_Flower_02_a.SM_Flower_02_a'"));
		GrassTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/StylizedProvencal/Meshes/SM_Flower_03_a.SM_Flower_03_a'"));
		GrassTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/StylizedProvencal/Meshes/SM_Flower_03_b.SM_Flower_03_b'"));
		GrassTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Catcafe/meshes/PLANTS/SM_redflower.SM_redflower'"));
		Tiles.Add(GrassTile);

		FTileData BushTile((int)ETileType::Bush, TArray<uint8>{ (int)ETileType::Bush, (int)ETileType::Grass, (int)ETileType::Tree, (int)ETileType::Path });
		BushTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Stylized_PBR_Nature/Foliage/Assets/SM_Bush.SM_Bush'"));
		BushTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Catcafe/meshes/PLANTS/bush/SM_bush.SM_bush'"));
		BushTile.SetMeshString(FString("/Script/Engine.StaticMesh'/Game/Fantastic_Village_Pack/meshes/environment/SM_ENV_PLANT_leaf_village.SM_ENV_PLANT_leaf_village'"));
		Tiles.Add(BushTile);
	}

	int SweepLayer(AWFCGrid* Grid, FCell* Cell, uint8 TileID, int32 Layer, std::function< int(FCell* Cell, uint8 TileID) >Func)
	{
		if (!Cell || !Grid) return -1;
		static int ret{ 0 };
		ret = 0;

		FCell* CurrentCell = Cell;
		FIntPoint StartPosition = { CurrentCell->GetGridPos().X - Layer, CurrentCell->GetGridPos().Y - Layer};

		// before moving to next cell, check if it exists
		// jump to cell in position X - Layer, Y - Layer
		if (WFCUtils::IsPositionWithinBounds(&StartPosition, Grid))
		{
			CurrentCell = &Grid->GetCells()[ StartPosition.X ][ StartPosition.Y ];
		}

		// repeat sequence 4 times
		// move right x Layer * 2 times
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < (Layer * 2); j++)
			{
				FIntPoint NextPosition;
				switch (i)
				{
				case 0: NextPosition = { CurrentCell->GetGridPos().X + 1, CurrentCell->GetGridPos().Y }; break;
				case 1: NextPosition = { CurrentCell->GetGridPos().X, CurrentCell->GetGridPos().Y - 1 }; break;
				case 2: NextPosition = { CurrentCell->GetGridPos().X - 1, CurrentCell->GetGridPos().Y }; break;
				case 3: NextPosition = { CurrentCell->GetGridPos().X, CurrentCell->GetGridPos().Y + 1 }; break;		
				}
				
				if (WFCUtils::IsPositionWithinBounds(&NextPosition, Grid))
				{
					// call std::function for each cell
					// accumulate what std::function returns and return it
					CurrentCell = &Grid->GetCells()[ NextPosition.X ][ NextPosition.Y ];
					ret += Func(CurrentCell, TileID);
				}
			}
		}
		return ret;
	}
}

namespace WFCWeightUtils
{
	static TArray< int > gTileCounts;

	void AddRandomWeight(float& weight, float min, float max)
	{
		weight += FMath::FRandRange(min, max);
	}

	int GetHighestWeightID(const TArray< float >& weights)
	{
		float highest = AWFCManager::sEntropyThreshold;
		int ret = -1;

		for (int i = 0; i < weights.Num(); i++)
		{		
			if (weights[ i ] == AWFCManager::sEntropyThreshold) continue;
			else if (weights[ i ] > highest)
			{
				highest = weights[ i ];
				ret = i;
			}
		}
		return ret;
	}

	auto CacheWeightData = [](FCell* Cell, uint8 TileID) -> int
	{	
		if (!Cell || !Cell->WaveFunction.Num()) return -1;
		else if (!Cell->bIsCollapsed) gTileCounts[ 0 ]++;
		else gTileCounts[ Cell->WaveFunction[ 0 ] ]++;
		return 0;
	};

	auto FindTiles = [](FCell* Cell, uint8 TileID) -> int
	{
		if (!Cell || !Cell->IsCollapsed() || !Cell->WaveFunction.Num()) return -1;
		else if (Cell->WaveFunction[ 0 ] == TileID) return 1;
		return 0;
	};

	float AccumulateWeights(AWFCGrid* Grid, FCell* Cell, uint8 TileID, int Layer)
	{
		if (!Cell || !Grid) return 0.f;
		float ret = 0.0f;

		// start at 1 to ignore unknown tile
		for (int i = 1; i < Cell->WaveFunction.Num(); i++)
		{
			// don't accumulate weights for unallowed tiles
			if (Cell->WFWeights[ i ] == AWFCManager::sEntropyThreshold) continue;

			WeightMap ArrayMap = *WFCData::WeightMaps[ Layer ];
			const std::unordered_map< ETileType, float >& Weights = ArrayMap[ TileID ];

			int TilesFound = WFCAlgorithm::SweepLayer(Grid, Cell, Cell->WaveFunction[ i ], Layer, FindTiles);

			auto It = Weights.find(static_cast< ETileType >(i));
			ret += TilesFound * It->second;
		}
		return ret;
	}

	float AccumulateWeightsOptimised(AWFCGrid* Grid, FCell* Cell, uint8 TileID, int Layer)
	{
		if (!Cell || !Grid) return 0.f;
		float ret = 0.0f;

		gTileCounts.Empty();
		gTileCounts.Init(0, Cell->WaveFunction.Num());

		WFCAlgorithm::SweepLayer(Grid, Cell, TileID, Layer, CacheWeightData);

		for (int i = 1; i < Cell->WaveFunction.Num(); i++)
		{
			// this tile is not allowed so skip it
			if (Cell->WFWeights[ i ] == AWFCManager::sEntropyThreshold) continue;

			WeightMap ArrayMap = *WFCData::WeightMaps[ Layer ];
			const std::unordered_map< ETileType, float >& Weights = ArrayMap[ TileID ];

			auto It = Weights.find(static_cast< ETileType >(i));
			ret += gTileCounts[ i ] * It->second;
		}
		return ret;
	}
}

namespace WFCWeightRules
{
	float gStartWeight = 1.0f;
	float gMaxLayers = 2;

	// for PATH:
	// IN current Path cell, OUT next Path cell (to be collapsed)
	FCell* PathRule(FCell* CurrentCell, TArray< FCell* >& NextCells)
	{
		if (!CurrentCell || !NextCells.Num()) return nullptr;
		int winnerCell{ 0 };

		TArray< float >Weights;
		Weights.Init(1.0f, NextCells.Num());


		for (int i = 0; i < Weights.Num(); i++)
		{
			Weights[ i ] += WFCData::PathDistanceWeights[ i ];
		}

		for (float& Weight : Weights)
		{
			WFCWeightUtils::AddRandomWeight(Weight, -0.2f, 0.2f);
		}

		TArray< int >NextCellsIndices;
		for (int i = 0; i < NextCells.Num(); i++)
		{
			NextCellsIndices.Add(i);
		}

		NextCellsIndices.Sort([ &Weights ](int A, int B) {
			return Weights[ A ] > Weights[ B ];
			});

		TArray< FCell* >SortedCells;
		for (int i = 0; i < NextCells.Num(); i++)
		{
			SortedCells.Add(NextCells[NextCellsIndices[ i ]]);
		}
		NextCells = SortedCells;

		TArray< FCell* > Cells;
		ProceduralPath::GetSurroundingCells(NextCells[ 0 ], Cells);

		if (NextCells.Num() == 1 || Cells.Num() >= 2) return NextCells[ 0 ];
		else if (Cells.Num() < 2 && NextCells.Num() > 1) return NextCells[ 1 ];
		else if (Cells.Num() < 2 && NextCells.Num() > 2) return NextCells[ 2 ];
		else return nullptr;

		// 1. Calculate distance for each cell from the target and sort it (Nearest to Farthest) 3 cells in total
		// 2. Deduct weight to each cell based on the distance (-0.2f, -0.5f, -0.8f).
		// 3. Add a random weight to each cell
		// 4. Return the cell with the highest weight
	}

#define OPTIMISE 
	float TreeRule(FCell* Cell)
	{
		float ret = gStartWeight;

		for (int i = 1; i <= gMaxLayers; i++)
		{
#ifdef OPTIMISE
			ret += WFCWeightUtils::AccumulateWeightsOptimised(Cell->Grid->GetGrid(), Cell, (uint8)ETileType::Tree, i);
#else 
			ret += WFCWeightUtils::AccumulateWeights(Cell->Grid->GetGrid(), Cell, (uint8)ETileType::Tree, i);
#endif
		}
		return ret;
	}

	float GrassRule(FCell* Cell)
	{
		float ret = gStartWeight;

		for (int i = 1; i <= gMaxLayers; i++)
		{
#ifdef OPTIMISE
			ret += WFCWeightUtils::AccumulateWeightsOptimised(Cell->Grid->GetGrid(), Cell, (uint8)ETileType::Grass, i);
#else
			ret += WFCWeightUtils::AccumulateWeights(Cell->Grid->GetGrid(), Cell, (uint8)ETileType::Grass, i);
#endif
		}
		return ret;
	}

	float BushRule(FCell* Cell)
	{
		float ret = gStartWeight;
	
		for (int i = 1; i <= gMaxLayers; i++)
		{
#ifdef OPTIMISE
			ret += WFCWeightUtils::AccumulateWeightsOptimised(Cell->Grid->GetGrid(), Cell, (uint8)ETileType::Bush, i);
#else
			ret += WFCWeightUtils::AccumulateWeights(Cell->Grid->GetGrid(), Cell, (uint8)ETileType::Bush, i);
#endif
		}
		return ret;
	}
}

