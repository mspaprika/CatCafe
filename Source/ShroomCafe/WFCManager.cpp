// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCManager.h"
#include "WFCUtils.h"
#include "DrawDebugHelpers.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "WFC.h"
#include "PG.h"
#include "TileSpawner.h"

const float AWFCManager::sEntropyThreshold{ -10.0f };
float AWFCManager::sMinMeshOffset{ 100.0f };
int32 AWFCManager::sTileSize{ 300 };
TArray< FTileData > AWFCManager::sTiles{};

// Sets default values
AWFCManager::AWFCManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// construction helpers are meant to be called in the constructor only. Other places need to use Loaders and Finders
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.Blueprint'/Game/WFC/TileMeshUnknown.TileMeshUnknown'"));
	WFCAlgorithm::GenerateWaveFunction(sTiles);
	
}

// Called when the game starts or when spawned
void AWFCManager::BeginPlay()
{
	Super::BeginPlay();
	TileSpawner = GetWorld()->SpawnActor< ATileSpawner >(ATileSpawner::StaticClass());
}

// Called every frame
void AWFCManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bGenerated)
	{
		// will be called from BP later - maybe?
		//OnProceduralGeneration();
		//bGenerated = true;
	}

	//DrawDebugGrid();
}

void AWFCManager::DrawDebugGrid()
{
	for (int Row = 0; Row < GridWidth; ++Row)
	{
		for (int Column = 0; Column < GridHeight; ++Column)
		{
			FCell& Cell = Grid->GetCells()[ Row ][ Column ];
			//DrawDebugBox(GetWorld(), Cell.GetWorldPos(), FVector(Grid->GetCellSize() / 2, Grid->GetCellSize() / 2, 1), FColor::Blue, false, -1.0f, 0, 2.0f);
		}
	}
}

void AWFCManager::InitializeGrid()
{
	Grid = GetWorld()->SpawnActor<AWFCGrid>(AWFCGrid::StaticClass());

	int Rows = GridWidth;
	int Columns = GridHeight;

	Grid->GetCells().SetNum(Rows);
	Grid->SetGridHeight(Columns);
	Grid->SetGridWidth(Rows);
	Grid->SetRandomness(Randomness);

	for (int Row = 0; Row < Rows; ++Row)
	{
		Grid->GetCells()[ Row ].SetNum(Columns);  // Create columns for each row
	}

	// Create cells
	for (int Row = 0; Row < Rows; ++Row)
	{
		for (int Column = 0; Column < Columns; ++Column)
		{
			FCell& Cell = Grid->GetCells()[ Row ][ Column ];
			Cell.Grid = this;
			Cell.GroundOffset = VerticalOffset;
			Cell.GridPos = { Row, Column };
			Cell.Size = TileSize;

			FVector ParentPos = GetActorLocation();

			// Copy wave function into the cell
			for (const FTileData& Tile : sTiles)
			{
				Cell.WaveFunction.Add(Tile.TileID);
			}

			Cell.WFWeights.Init(1.0f, Cell.WaveFunction.Num());
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Grid Initialized!"));
}

void AWFCManager::GenerateGrid()
{
	for (auto Path : WFCData::PathCoords)
	{
		if (Grid->GetGridWidth() < 150 || Grid->GetGridHeight() < 150) break;
		FIntPoint& PathStart = Path[ 0 ];
		FIntPoint& PathEnd = Path[ 1 ];

		ProceduralPath::Generate
		(
			Grid,
			&Grid->GetCells()[PathStart.X][PathStart.Y], // start of path
			&Grid->GetCells()[PathEnd.X][PathEnd.Y], // end of path
			this->GetWorld()
		);
	}

	ProceduralWorld::Generate(Grid, this->GetWorld());
}

void AWFCManager::SpawnGrid()
{
	for (int Row = 0; Row < GridWidth; Row++)
	{
		for (int Column = 0; Column < GridHeight; Column++)
		{
			FCell& Cell = Grid->GetCells()[ Row ][ Column ];

			// Tile 0 == collapsed WF
			uint8 ChosenTile = Cell.WaveFunction[ 0 ];

			// don't spawn any tiles in middle perimeter
			if (Cell.GridPos.X >= MiddlePerimeterBottomLeft.X && Cell.GridPos.X <= MiddlePerimeterTopRight.X &&
				Cell.GridPos.Y >= MiddlePerimeterBottomLeft.Y && Cell.GridPos.Y <= MiddlePerimeterTopRight.Y)
			{
				continue;
			}

			TileSpawner->SpawnTile(this->GetWorld(), &Cell, ChosenTile);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Grid Spawned!"));
}

void AWFCManager::OnProceduralGeneration()
{
	UE_LOG(LogTemp, Warning, TEXT("Procedural Generation"));

	// Create grid and cells
	InitializeGrid();

	// WFC Algorithm
	GenerateGrid();

	// Spawn collapsed tiles in the worldS
	//SpawnGrid();
}


const TCHAR* AWFCManager::GetMeshString(uint8 TileID)
{
	for (FTileData& Tile : sTiles)
	{
		if (Tile.TileID == TileID)
		{
			if (!Tile.MeshStrings.Num())
			{
				UE_LOG(LogTemp, Warning, TEXT("No mesh strings found for tile %d"), TileID);
				return nullptr;
			}
			if (Tile.MeshStrings.Num() == 1)
			{
				return *Tile.MeshStrings[ 0 ];
			}
			int rand = FMath::RandRange(0, Tile.MeshStrings.Num() - 1);
			return *Tile.MeshStrings[ rand ];
		}
	}
	return nullptr;
}

