#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResultStruct.generated.h"

USTRUCT(BlueprintType)
struct FKuzuDBQueryResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "KuzuDB")
    bool Success;

    UPROPERTY(BlueprintReadWrite, Category = "KuzuDB")
    FString ErrorMessage;

    UPROPERTY(BlueprintReadWrite, Category = "KuzuDB")
    TArray<FString> QueryResults;
};