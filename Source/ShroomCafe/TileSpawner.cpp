// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSpawner.h"
#include "Components/CapsuleComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Tile.h"
#include "WFCManager.h"
#include "WFCUtils.h"
#include "TileSpawnRule.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATileSpawner::ATileSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AActor> BPActor(TEXT("/Script/Engine.Blueprint'/Game/WFC/BP_Rock.BP_Rock_C'"));
	if (BPActor.Succeeded())
	{
		BPClassRockTile = BPActor.Class;
	}
}

// Called when the game starts or when spawned
void ATileSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATileSpawner::SpawnTile(UWorld* World, FCell* Cell, uint8 TileID)
{
	if (!World || !Cell) return;
	
	ATile* Tile = SpawnTileInWorld(World, TileID);
	TileSpawnRule SpawnRule;

	if (Tile)
	{
		Tile->SetActorLocation(Cell->GetWorldPos());
		SpawnRule.SetMesh(Tile, &AWFCManager::sTiles[ TileID ], TileID);
		SpawnRule.SetCapsule(Tile, TileID);
	}
}


ATile* ATileSpawner::SpawnTileInWorld(UWorld* World, uint8 TileID)
{
	if (!World) return nullptr;
	ATile* NewTile{ nullptr };

	if (TileID == static_cast< uint8 >(ETileType::Path))
	{
		AWFCManager* Manager = Cast< AWFCManager >(UGameplayStatics::GetActorOfClass(World, AWFCManager::StaticClass()));
		ATileSpawner* TileSpawner = Cast< ATileSpawner >(UGameplayStatics::GetActorOfClass(World, ATileSpawner::StaticClass()));

		// Ensure the class is valid before spawning
		if (TileSpawner->GetRockTile())
		{
			AActor* SpawnedActor = World->SpawnActor<AActor>(TileSpawner->GetRockTile());
			if (SpawnedActor)
			{
				NewTile = Cast< ATile >(SpawnedActor);
			}
		}
	}
	else
	{
		FActorSpawnParameters SpawnParams;
		NewTile = World->SpawnActor< ATile >(ATile::StaticClass());
	}
	return NewTile;
}



