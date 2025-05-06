// Fill out your copyright notice in the Description page of Project Settings.


#include "UQuestManager.h"
#include "Types.h"

// track the current quest and poll for tags of completion status
// get player's ability system component and trigger game ability by posting gameplay event
// in game ability, it will apply different effect based on state (started, progress, completed)
// TMap<FName, FGameplayTag> QuestToCompletionTag; ---> store quest types with corresponding tags

