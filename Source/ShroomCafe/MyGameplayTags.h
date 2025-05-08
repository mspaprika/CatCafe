
#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"



struct FMyGameplayTags
{
    static const FMyGameplayTags& Get() { return Instance; }
    static void InitializeNativeTags();

    const TArray<FGameplayTag>& GetEventTags() const { return EventTags; }
    const TArray<FGameplayTag>& GetStatusTags() const { return StatusTags; }
    const TArray<FGameplayTag>& GetOtherTags() const { return OtherTags; }

private:
    TArray<FGameplayTag> EventTags;
    TArray<FGameplayTag> StatusTags;
    TArray<FGameplayTag> OtherTags;

    static FMyGameplayTags Instance;

    static FGameplayTag AddTag(FName TagName, FString TagComment);
};
