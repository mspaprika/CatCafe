// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"



USTRUCT(BlueprintType)
struct FTileData
{
	GENERATED_BODY()

	FVector2D WorldPos;
	uint8 TileID{ 0 };
	TArray<uint8> AllowedNeighbors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	FString MeshString;

	TArray< FString >MeshStrings;

	void SetMeshString(FString Mesh) { MeshStrings.Add(Mesh); }
	bool IsAllowedNeighbor(uint8 NeighborID) const { return AllowedNeighbors.Contains(NeighborID); }

	FTileData() {}
	FTileData(uint8 ID, TArray< uint8 > Neighbors) :
		TileID(ID), AllowedNeighbors(Neighbors) {}
};



UCLASS()
class SHROOMCAFE_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	TArray< UStaticMeshComponent* >Meshes;
};
