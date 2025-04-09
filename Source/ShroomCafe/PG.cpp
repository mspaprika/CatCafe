#include "PG.h"
#include "WFCManager.h"
#include "WFC.h"
#include "WFCUtils.h"
#include  "TileSpawner.h"


namespace ProceduralPath
{
	void Generate(AWFCGrid* Grid, FCell* Start, FCell* End, UWorld* World)
	{
		if (!Grid || !Start || !End) return;
		

		static ATileSpawner* TileSpawner{ World->SpawnActor< ATileSpawner >(ATileSpawner::StaticClass()) };

		FCell* CurrentCell = Start;
		FVector CurrentPos = CurrentCell->GetWorldPos();
		FVector TargetPos = End->GetWorldPos();
		bool bTargetReached = false;

		TArray< FCell* > NextCells;

		Start->SetWeight(static_cast< int >(ETileType::Path), 100.0f);
		WFCAlgorithm::CollapseCell(Start);

		while (!bTargetReached)
		{
			GetSurroundingCells(CurrentCell, NextCells);
			// sort by distance to target
			WFCUtils::SortCellsByDistance(End, NextCells);
			// apply path rule to get next cell
			FCell* NextCell = WFCWeightRules::PathRule(CurrentCell, NextCells);

			if (!NextCell)
			{
				UE_LOG(LogTemp, Warning, TEXT("Path Generation Failed!"));
				return;
			}

			if (NextCell == End)
			{
				bTargetReached = true;
				break;
			}
			// set weight very large to make sure it collapses
			NextCell->SetWeight(static_cast< int >(ETileType::Path), 100.0f);
			WFCAlgorithm::CollapseCell(NextCell);
			TileSpawner->SpawnTile(World, NextCell, NextCell->WaveFunction[0]);

			CurrentCell = NextCell;
			NextCells.Empty();
		}

		UE_LOG(LogTemp, Warning, TEXT("Path Generated!"));
	}


	void GetSurroundingCells(FCell* Current, TArray< FCell* >& Next)
	{
		if (!Current) return;
		FIntPoint CurrentPos = Current->GetGridPos();

		if (CurrentPos.X + 1 < Current->Grid->GetGridWidth())
		{
			FIntPoint NextPos = { CurrentPos.X + 1, CurrentPos.Y };
			FCell* NextCell = &Current->Grid->GetGrid()->GetCellAtPosition(NextPos);

			if (!NextCell->bIsCollapsed) Next.Add(NextCell);
		}
		if (CurrentPos.X - 1 >= 0)
		{
			FIntPoint NextPos = { CurrentPos.X - 1, CurrentPos.Y };
			FCell* NextCell = &Current->Grid->GetGrid()->GetCellAtPosition(NextPos);

			if (!NextCell->bIsCollapsed) Next.Add(NextCell);
		}
		if (CurrentPos.Y + 1 < Current->Grid->GetGridHeight())
		{
			FIntPoint NextPos = { CurrentPos.X, CurrentPos.Y + 1 };
			FCell* NextCell = &Current->Grid->GetGrid()->GetCellAtPosition(NextPos);

			if (!NextCell->bIsCollapsed) Next.Add(NextCell);
		}
		if (CurrentPos.Y - 1 >= 0)
		{
			FIntPoint NextPos = { CurrentPos.X, CurrentPos.Y - 1 };
			FCell* NextCell = &Current->Grid->GetGrid()->GetCellAtPosition(NextPos);

			if (!NextCell->bIsCollapsed) Next.Add(NextCell);
		}
	}
}

namespace ProceduralWorld
{
	FCell* FindLowestEntropyCell(AWFCGrid* Grid)
	{
		if (!Grid) return nullptr;

		int LowestEntropy = 10;
		FCell* LowestEntropyCell = nullptr;

		for (TArray< FCell >& Row : Grid->GetCells())
		{
			for (FCell& Cell : Row)
			{  
				// will improve later - GetEntropy is costly / might help if stored as variable
				if (!Cell.bIsCollapsed && Cell.GetEntropy() <= LowestEntropy)
				{			
					LowestEntropy = Cell.GetEntropy();
					LowestEntropyCell = &Cell;			
				}
			}
		}
		return LowestEntropyCell;
	}

	

	void Generate(AWFCGrid* Grid, UWorld* World)
	{
		if (!Grid) return;
		bool bIsGridEmpty = false;
		static ATileSpawner* TileSpawner{ World->SpawnActor< ATileSpawner >(ATileSpawner::StaticClass()) };

		while (!bIsGridEmpty)
		{
			FCell* Cell = FindLowestEntropyCell(Grid);

			if (!Cell)
			{
				bIsGridEmpty = true;
				break;
			}

			for (uint8 TileID : Cell->WaveFunction)
			{
				auto It = WFCData::TileRarity.find(static_cast< ETileType >(TileID));
				float CurrentWeight = Cell->GetWeight(TileID) * It->second;
				float randWeight = Grid->GetRandomness();

				switch (TileID)
				{
				case static_cast<int> (ETileType::Unknown):
				case static_cast<int> (ETileType::Path): 
					Cell->SetWeight(TileID, AWFCManager::sEntropyThreshold); break;

				case static_cast< int >(ETileType::Tree):
					Cell->SetWeight(TileID, WFCWeightRules::TreeRule(Cell) + FMath::FRandRange(-randWeight, randWeight));
					break;

				case static_cast< int >(ETileType::Bush):
					Cell->SetWeight(TileID, WFCWeightRules::BushRule(Cell) + FMath::FRandRange(-randWeight, randWeight));
					break;

				case static_cast< uint8 >(ETileType::Grass):
					Cell->SetWeight(TileID, WFCWeightRules::GrassRule(Cell) + FMath::FRandRange(-randWeight, randWeight));
					break;

				default:
					UE_LOG(LogTemp, Warning, TEXT("Invalid Tile ID"));
					break;
				}
			}

			WFCAlgorithm::CollapseCell(Cell);
			TileSpawner->SpawnTile(World, Cell, Cell->WaveFunction[0]);
			WFCAlgorithm::PropagateConstraints(Cell);
		}
	}
}