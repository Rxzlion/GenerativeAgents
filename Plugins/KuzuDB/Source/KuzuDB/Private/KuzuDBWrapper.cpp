#include "KuzuDBWrapper.h"

bool UKuzuDBWrapper::CreateDatabase(const FString& DBPath)
{
    kuzu_system_config config = kuzu_default_system_config();
    Database = new kuzu_database();
    kuzu_state state = kuzu_database_init(TCHAR_TO_UTF8(*DBPath), config, Database);
    if (state != KuzuSuccess)
    {
        LastError = TEXT("Failed to create database");
        return false;
    }
    return true;
}

bool UKuzuDBWrapper::ConnectToDatabase(const FString& DBPath)
{
    Connection = new kuzu_connection();
    kuzu_state state = kuzu_connection_init(Database, Connection);
    if (state != KuzuSuccess)
    {
        LastError = TEXT("Failed to connect to database");
        return false;
    }
    return true;
}

FKuzuDBQueryResult UKuzuDBWrapper::ExecuteQuery(const FString& Query)
{
    FKuzuDBQueryResult result;
    result.Success = false;
    result.ErrorMessage = "";
    result.QueryResults.Empty();

    kuzu_query_result* queryResult = new kuzu_query_result();
    kuzu_state state = kuzu_connection_query(Connection, TCHAR_TO_UTF8(*Query), queryResult);
    if (state != KuzuSuccess)
    {
        char* errorMessage = kuzu_query_result_get_error_message(queryResult);
        if (errorMessage != NULL && errorMessage[0] != '\0') 
        {
            result.ErrorMessage = errorMessage;
        }
        else
        {
            result.ErrorMessage = TEXT("Failed to execute query");
        }
        kuzu_destroy_string(errorMessage);
        kuzu_query_result_destroy(queryResult);
        return result;
    }
    result.Success = kuzu_query_result_is_success(queryResult);
    if (!result.Success)
    {
        result.ErrorMessage = kuzu_query_result_get_error_message(queryResult);
        kuzu_query_result_destroy(queryResult);
        return result;
    }

    while (kuzu_query_result_has_next(queryResult))
    {
        kuzu_flat_tuple* tuple = new kuzu_flat_tuple();
        kuzu_query_result_get_next(queryResult, tuple);

        char* stringValue = kuzu_flat_tuple_to_string(tuple);
        FString stringUE = FString(UTF8_TO_TCHAR(stringValue)); // Convert C-style string to FString
        result.QueryResults.Add(stringUE); // Add FString to TArray
        kuzu_flat_tuple_destroy(tuple);
    }
    kuzu_query_result_destroy(queryResult);
    return result;
}

TArray<FString> UKuzuDBWrapper::GetQueryResults(const FString& Query)
{

}

bool UKuzuDBWrapper::DisconnectFromDatabase()
{

}

bool UKuzuDBWrapper::IsConnected()
{
}

FString UKuzuDBWrapper::GetLastError()
{
  
}