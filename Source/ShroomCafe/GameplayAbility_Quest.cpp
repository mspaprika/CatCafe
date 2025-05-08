// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Quest.h"
#include "MyGameplayTags.h"

// trigger: gameplay events: Event.Quest.Completed
// apply different gameplay efgfects based on a quest
// set tags like Quest.Status.Completed
//



UGameplayAbility_Quest::UGameplayAbility_Quest()
{
}

void UGameplayAbility_Quest::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{

	StartQuest(Handle, ActorInfo);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGameplayAbility_Quest::InitAbility()
{
	const TArray<FGameplayTag>& EventTags = FMyGameplayTags::Get().GetEventTags();

	for (auto& Tag : EventTags)
	{
		FAbilityTriggerData TriggerData;

		TriggerData.TriggerTag = Tag;
		TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;

		AbilityTriggers.Add(TriggerData); // activates when gameplay event is received
		ActivationOwnedTags.AddTag(Tag);
	}
}

void UGameplayAbility_Quest::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	InitAbility();
}

void UGameplayAbility_Quest::StartQuest(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo)
{
	int test = 0;
}

void UGameplayAbility_Quest::CompleteQuest(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo)
{

}

void UGameplayAbility_Quest::ProgressQuest(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo)
{

}