// MyGameplayTags.cpp

#include "MyGameplayTags.h"
#include "GameplayTagsManager.h"

FMyGameplayTags FMyGameplayTags::Instance;

void FMyGameplayTags::InitializeNativeTags()
{
    UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

    Instance.EventTags.Add(AddTag(TEXT("Event.Quest.Started"), TEXT("Tag for started quests")));
    Instance.EventTags.Add(AddTag(TEXT("Event.Quest.Completed"), TEXT("Tag for completed quests")));
}

FGameplayTag FMyGameplayTags::AddTag(FName TagName, FString TagComment)
{
    FGameplayTag Tag = UGameplayTagsManager::Get().AddNativeGameplayTag(TagName, TagComment);
    return Tag;
}