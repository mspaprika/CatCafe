#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Types.generated.h"

UENUM(BlueprintType)
enum class EQuestID : uint8
{
    None             UMETA(DisplayName = "None"),
    FindCatTree          UMETA(DisplayName = "Find the Cat Tree"),
    VisitSaloon UMETA(DisplayName = "Visit Saloon"),
    FreeMushrooms     UMETA(DisplayName = "Free mushrooms")
};