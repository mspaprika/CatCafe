// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileSpawner.generated.h"

class AWFCManager;
struct FCell;
class ATile;


UCLASS()
class SHROOMCAFE_API ATileSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileSpawner();
	UClass* GetRockTile() { return BPClassRockTile; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UClass* BPClassRockTile{ nullptr };
	ATile* SpawnTileInWorld(UWorld* World, uint8 TileID);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnTile(UWorld* World, FCell* Cell, uint8 TileID);
};
