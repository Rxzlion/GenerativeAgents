#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KuzuWrapper.h"
#include "ResultStruct.h"
#include "KuzuDBWrapper.generated.h"

UCLASS()
class KUZUDB_API UKuzuDBWrapper : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "KuzuDB")
    FKuzuDBQueryResult ExecuteQuery(const FString& Query);

    UFUNCTION(BlueprintCallable, Category = "KuzuDB")
    TArray<FString> GetQueryResults(const FString& Query);

    UFUNCTION(BlueprintCallable, Category = "KuzuDB")
    bool CreateDatabase(const FString& DBPath);

    UFUNCTION(BlueprintCallable, Category = "KuzuDB")
    bool ConnectToDatabase(const FString& DBPath);

    // Add these new functions:
    UFUNCTION(BlueprintCallable, Category = "KuzuDB")
    bool DisconnectFromDatabase();

    UFUNCTION(BlueprintPure, Category = "KuzuDB")
    bool IsConnected();

    UFUNCTION(BlueprintCallable, Category = "KuzuDB")
    FString GetLastError();


private:
    kuzu_database* Database;
    kuzu_connection* Connection;
    FString LastError;
};