// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Types.h"

UQuestAttributeSet::UQuestAttributeSet()
{
    QuestStatus = static_cast< float >(EQuestID::FindCatTree);
}

void UQuestAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UQuestAttributeSet, QuestStatus);

    DOREPLIFETIME(UQuestAttributeSet, ActiveQuest);
}

void UQuestAttributeSet::OnRep_QuestStatusUpdated(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UQuestAttributeSet, QuestStatus, OldValue);
}

void UQuestAttributeSet::OnRep_ActiveQuestUpdated(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UQuestAttributeSet, ActiveQuest, OldValue);
}

void UQuestAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetQuestStatusAttribute())
    {
        float NewValue = GetQuestStatus();
        // Log or trigger event
    }

    if (Data.EvaluatedData.Attribute == GetActiveQuestAttribute())
    {
        float NewValue = GetActiveQuest();
        // Log or trigger event
    }
}
