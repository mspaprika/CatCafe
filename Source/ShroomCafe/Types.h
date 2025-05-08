#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Types.generated.h"


UENUM(BlueprintType)
enum class EQuestID : uint8
{
    None              UMETA(DisplayName = "None"),
    FindCatTree       UMETA(DisplayName = "Find the Cat Tree"),
    VisitSaloon       UMETA(DisplayName = "Visit Saloon"),
    FreeMushrooms     UMETA(DisplayName = "Free Mushrooms"),

    MaxQuests         UMETA(DisplayName = "Max Quests"),
};

UENUM(BlueprintType)
enum class EQuestState : uint8
{
    NotStarted       UMETA(DisplayName = "Quest not Started"),
    Started          UMETA(DisplayName = "Quest Started"),
    InProgress       UMETA(DisplayName = "Quest in Progress"),
    Completed        UMETA(DisplayName = "Quest Completed"),

    MaxStates        UMETA(DisplayName = "Max States"),
};