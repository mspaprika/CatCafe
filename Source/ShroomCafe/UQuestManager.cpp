// Fill out your copyright notice in the Description page of Project Settings.

#include "UQuestManager.h"
#include "CoreMinimal.h"

#include "QuestAttributeSet.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "MyGameplayTags.h"
#include "Kismet/GameplayStatics.h"


// track the current quest and check attributes for quest status
// get player's ability system component and trigger game ability by posting gameplay event
// in game ability, it will apply different effect based on state (started, progress, completed)
// //  gameplay effects will be created in the Blueprint

// Create data carrier QuestData (Description, status, quest string)
// TMap<EQuestId, FQuestData> QuestToData;

// Create Delegate OnQuestUpdated and subscribe in ui manager

void UUQuestManager::Init(ACharacter* Owner)
{
	pPlayer = static_cast< ACatCharacter* >(Owner);

	if (pPlayer)
	{
		ASC = pPlayer->GetAbilitySystemComponent();
		ASC->AddSet<UQuestAttributeSet>();
	}
}

void UUQuestManager::UpdateQuests()
{
	ACharacter* pChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	pPlayer = static_cast<ACatCharacter*>(pChar);

	ASC = pPlayer->GetAbilitySystemComponent();
	const UQuestAttributeSet* QuestAttributes = ASC->GetSet<UQuestAttributeSet>();
	
	QuestStatus = static_cast<EQuestState>(QuestAttributes->QuestState.GetCurrentValue());
	switch (QuestStatus)
	{
	case EQuestState::NotStarted:
	{
		FGameplayEventData EventData;
		EventData.EventTag = FGameplayTag::RequestGameplayTag("Event.Quest.Started");
		EventData.Instigator = pPlayer;
		EventData.Target = pPlayer;

		if (ASC)
		{
			ASC->HandleGameplayEvent(EventData.EventTag, &EventData);

			ASC->SetNumericAttributeBase(QuestAttributes->GetActiveQuestAttribute(), static_cast<float>(GetNextQuestId()));
			ASC->SetNumericAttributeBase(QuestAttributes->GetQuestStateAttribute(), static_cast<float>(EQuestState::Started));
		}
	}
	break;
	case EQuestState::Started:
	{

	}
	break;
	default: break;
	}

	// fire delegate
}

EQuestID UUQuestManager::GetNextQuestId() const
{
	uint8 ret = (static_cast< uint8 >(ActiveQuest) + 1u) % static_cast< uint8 >(EQuestID::MaxQuests);
	return static_cast< EQuestID >(ret);
}
