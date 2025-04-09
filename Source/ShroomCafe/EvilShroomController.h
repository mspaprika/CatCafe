// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Delegates/DelegateCombinations.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "EvilShroomController.generated.h"

/**
 * 
 */



UCLASS()
class SHROOMCAFE_API AEvilShroomController : public AAIController
{
	GENERATED_BODY()

	AEvilShroomController();
	
public:

    // Delegate to notify animation state change
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeAnimation, FName, NewAnimState);


    UPROPERTY(BlueprintAssignable, Category = "Animation")
    FOnChangeAnimation OnChangeAnimation;


	// Function to notify animation change
	UFUNCTION(BlueprintCallable, Category = "AI")
	void NotifyChangeAnimation(FName NewAnimState) const ;
};
