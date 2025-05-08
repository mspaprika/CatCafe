// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbility.h"
#include "CatCharacter.h"
#include "UQuestManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SHROOMCAFE_API UUQuestManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init(ACharacter* Owner);

	UPROPERTY()
	UAbilitySystemComponent* ASC;

	UPROPERTY()
	ACatCharacter* pPlayer;

	UFUNCTION(BlueprintCallable)
	void UpdateQuests();

private:
	bool QuestStarted{ false };
protected:
	EQuestID ActiveQuest{ EQuestID::None };
	EQuestState QuestStatus{ EQuestState::NotStarted };

	EQuestID GetNextQuestId() const;
};
