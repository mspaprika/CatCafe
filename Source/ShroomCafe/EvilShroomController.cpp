// Fill out your copyright notice in the Description page of Project Settings.



#include "EvilShroomController.h"





AEvilShroomController::AEvilShroomController()
{
	// Initialize the delegate
	//OnChangeAnimation = FOnChangeAnimation();
}


void AEvilShroomController::NotifyChangeAnimation(FName NewAnimState) const
{
	OnChangeAnimation.Broadcast(NewAnimState);
}