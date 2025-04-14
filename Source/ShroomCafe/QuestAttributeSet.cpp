// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestAttributeSet.h"
#include "Net/UnrealNetwork.h"

UQuestAttributeSet::UQuestAttributeSet()
{
}

void UQuestAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UQuestAttributeSet, MushroomsCollected);
}

void UQuestAttributeSet::OnRep_MushroomsCollected(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UQuestAttributeSet, MushroomsCollected, OldValue);
}

void UQuestAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetMushroomsCollectedAttribute())
    {
        float NewValue = GetMushroomsCollected();
        // Log or trigger event
    }
}
