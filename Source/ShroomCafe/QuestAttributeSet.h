// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"         // For FGameplayEffectModCallbackData
#include "Net/UnrealNetwork.h"
#include "QuestAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class SHROOMCAFE_API UQuestAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UQuestAttributeSet();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Quest", ReplicatedUsing = OnRep_QuestStatusUpdated)
	FGameplayAttributeData QuestStatus;
	ATTRIBUTE_ACCESSORS(UQuestAttributeSet, QuestStatus)

	UPROPERTY(BlueprintReadOnly, Category = "Quest", ReplicatedUsing = OnRep_ActiveQuestUpdated)
	FGameplayAttributeData ActiveQuest;
	ATTRIBUTE_ACCESSORS(UQuestAttributeSet, ActiveQuest)

	UFUNCTION()
	void OnRep_QuestStatusUpdated(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_ActiveQuestUpdated(const FGameplayAttributeData& OldValue);
};
