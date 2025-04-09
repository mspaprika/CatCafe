// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCGrid.h"


// Sets default values
AWFCGrid::AWFCGrid(int rows, int columns, TArray<FTileData>& tiles)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWFCGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWFCGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FCell& AWFCGrid::GetCellAtPosition(FIntPoint& pos)
{
	return Cells[ pos.X ][ pos.Y ];
}


