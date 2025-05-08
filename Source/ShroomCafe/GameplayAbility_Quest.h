// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "GameplayAbility_Quest.generated.h"

/**
 * 
 */
UCLASS()
class SHROOMCAFE_API UGameplayAbility_Quest : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGameplayAbility_Quest();

	UPROPERTY(EditDefaultsOnly, Category = "Quest")
	FGameplayTag QuestTag;

	UPROPERTY(EditDefaultsOnly, Category = "Quest")
	FText QuestDescription;


	UFUNCTION(BlueprintCallable, Category = "Quest")
	void InitAbility();

	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	
	void StartQuest(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo);

	
	void CompleteQuest(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo);

	
	void ProgressQuest(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo);
	
};
