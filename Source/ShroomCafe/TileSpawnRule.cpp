// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSpawnRule.h"
#include "WFCManager.h"
#include "Components/CapsuleComponent.h"
#include "WFCUtils.h"



TileSpawnRule::TileSpawnRule()
{

}

TileSpawnRule::~TileSpawnRule()
{

}

int TileSpawnRule::GetObjectCount(int TileID)
{
	switch (TileID)
	{
	case static_cast< int >(ETileType::Path): return 1;
	case static_cast< int >(ETileType::Tree): return 1;
	case static_cast< int >(ETileType::Grass): return FMath::RandRange(3, 6);
	case static_cast< int >(ETileType::Bush): return FMath::RandRange(3, 4);
	default: return 0;
	}
}

float TileSpawnRule::GetScale(int TileID)
{
	switch (TileID)
	{
	case static_cast< int >(ETileType::Path): return 1.0f;
	case static_cast< int >(ETileType::Tree): return FMath::RandRange(0.7f, 1.5f);
	case static_cast< int >(ETileType::Grass): return FMath::RandRange(0.5f, 1.1f);
	case static_cast< int >(ETileType::Bush): return FMath::RandRange(0.3f, 1.7f);
	default: return 1.0f;
	}
}


void TileSpawnRule::SetCapsule(ATile* Tile, int TileID)
{
	if (!Tile || TileID != static_cast< int >(ETileType::Tree)) return;
	
	UCapsuleComponent* CapsuleComp = NewObject<UCapsuleComponent>(Tile, UCapsuleComponent::StaticClass());
	CapsuleComp->AttachToComponent(Tile->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	float height;
	float radius;

	float scale = Tile->GetActorScale().X;

	if (scale < 1.0f)
	{
		height = 100.0f;
		radius = 50.0f;
	}
	else if (scale < 1.3f)
	{
		height = 150.0f;
		radius = 60.0f;
	}
	else
	{
		height = 200.0f;
		radius = 70.0f;
	}

	CapsuleComp->SetCapsuleHalfHeight(height);
	CapsuleComp->SetCapsuleRadius(radius);

	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);  // Treats the capsule as a dynamic object
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Block);  // Block all interactions

	CapsuleComp->RegisterComponent();  // Register the component to make it functional
}

void TileSpawnRule::SetMesh(ATile* Tile, FTileData* Data, int TileID)
{
	if (!Tile || !Data) return;
	int ObjectCount = GetObjectCount(TileID);

	for (int i = 0; i < ObjectCount; i++)
	{
		// Setup Mesh Component
		UStaticMeshComponent* NewMeshComp = NewObject<UStaticMeshComponent>(Tile);
		NewMeshComp->AttachToComponent(Tile->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

		// Setup Mesh Asset
		UStaticMesh* MeshAsset = LoadObject< UStaticMesh >(nullptr, AWFCManager::GetMeshString(TileID));
		NewMeshComp->SetStaticMesh(MeshAsset);
		NewMeshComp->SetRelativeRotation(FRotator(0.0f, FMath::FRandRange(0.f, 360.f), 0.0f));

		// TODO: Make functions for random rotation and wrapper for position
		if (TileID != static_cast<uint8>(ETileType::Tree) && TileID != static_cast<uint8>(ETileType::Path))
		{
			FVector2D planePos = WFCUtils::GetRandomPosition(AWFCManager::sTileSize, 6.28f / (i + 1));
			NewMeshComp->SetRelativeLocation(FVector(planePos.X, planePos.Y, 0.0f));
		}

		// Setup scale and collision params
		float Scale = GetScale(TileID);
		NewMeshComp->SetWorldScale3D(FVector(Scale));
		NewMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		NewMeshComp->RegisterComponent();

		Tile->Meshes.Add(NewMeshComp);
	}
}


