// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Types.h"

UQuestAttributeSet::UQuestAttributeSet()
{
    ActiveQuest = static_cast< float >(EQuestID::None);
    QuestState = static_cast< float >(EQuestState::NotStarted);
}

void UQuestAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UQuestAttributeSet, QuestState);

    DOREPLIFETIME(UQuestAttributeSet, ActiveQuest);
}

void UQuestAttributeSet::OnRep_QuestStatusUpdated(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UQuestAttributeSet, QuestState, OldValue);
}

void UQuestAttributeSet::OnRep_ActiveQuestUpdated(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UQuestAttributeSet, ActiveQuest, OldValue);
}

void UQuestAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetQuestStateAttribute())
    {
        float NewValue = GetQuestState();
        // Log or trigger event
    }

    if (Data.EvaluatedData.Attribute == GetActiveQuestAttribute())
    {
        float NewValue = GetActiveQuest();
        // Log or trigger event
    }
}
