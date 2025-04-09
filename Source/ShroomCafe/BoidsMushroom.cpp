// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidsMushroom.h"

// Sets default values
ABoidsMushroom::ABoidsMushroom()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoidsMushroom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoidsMushroom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoidsMushroom::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

