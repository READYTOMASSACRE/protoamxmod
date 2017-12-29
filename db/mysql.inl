/**
 * MySQL - работа с бд
 */

/**
 * Создает подключение к бд
 *
 * @param &Handle:connect
 * @param &Handle:tuple
 */
bool:MySQL_Init( &Handle:connect, &Handle:tuple ) {
    // Determine the database information
    new host[64], username[32], password[32], database[128], error[256], errNum

    get_pcvar_string( Cvar_proto_mysql_dbhost	, host		    , 63	)
    get_pcvar_string( Cvar_proto_mysql_dbuser	, username		, 31	)
    get_pcvar_string( Cvar_proto_mysql_dbpass	, password		, 31	)
    get_pcvar_string( Cvar_proto_mysql_dbname	, database		, 127	)

    // Set up the tuple that will be used for threading
    tuple = SQL_MakeDbTuple( host, username, password, database )

    // Attempt to connect
    connect = SQL_Connect( tuple, errNum, error, 255 )

    if ( !connect ) {
       log_amx("[MySQL] Database connection failed: [%d] %s", errNum, error)

       return false
    }

    log_amx( "[MySQL] Connection established successfuly" )

    MySQL_CreateTables( connect )

    MySQL_connectionState = true

    return true
}

/**
 * Закрывает подключение к бд
 *
 * @param &Handle:connect
 * @param &Handle:tuple
 */
bool:MySQL_Close( &Handle:connect, &Handle:tuple ) {
    if ( connect ) SQL_FreeHandle( connect )
    if ( tuple ) SQL_FreeHandle( tuple )

    MySQL_connectionState = false

    return false
}

/**
 * MySQL исключение
 *
 * @param Handle:query
 * @param string[]
 * @param integer
 */
bool:MySQL_Error( Handle:query, queryString[], id ) {
    new error[256]
    new errNum = SQL_QueryError(query, error, 255)

    log_amx("[MySQL] Quering error, id: [%d]", id)
    log_amx("[MySQL] Message: %s [%d]", error, errNum)
    log_amx("[MySQL] Query statement: %s", queryString)

    SQL_FreeHandle( query)

    if (errNum == MYSQL_ERR_TIMEOUT) {
        MySQL_connectionState = MySQL_Close(MySQL_Connect, MySQL_Tuple)
        MySQL_connectionState = MySQL_Init(MySQL_Connect, MySQL_Tuple)
    }

    return true
}

/**
 * Выполняет запрос к бд
 *
 * @param Handle:connect
 * @param string[]
 */
Trie:MySQL_Query( Handle:connect, queryString[] ) {
    new buffer[512]

    SQL_QuoteString( connect, buffer, 511, queryString)

    new Handle:query = SQL_PrepareQuery( connect, buffer )
    new Trie:result = CreateTrie()

    MySQL_Parse( query, result )
    SQL_FreeHandle( query )

    return result
}

/**
 * Парсит запрос к бд
 *
 * @param Handle:query
 * @param &Trie:result
 */
Trie:MySQL_Parse( Handle:query, &Trie:result ) {
    while ( SQL_MoreResults( query ) ) {
        new result[], length = SQL_NumColumns( query )

        for (new column = 0; column <= length; column++ ) {
            new field[64]
            SQL_FieldNumToName( query, column, field, 63 )
            TrieSetString(result, SQL_ReadResult ( query, column ), field)
        }

        SQL_NextRow ( query )
    }
}

/**
 * Проверяет соединение с бд
 */
bool:MySQL_IsConnected() {
    return MySQL_connectionState == true
}

bool:MySQL_CreateTables( Handle:connect ) {
    new Handle:query

    for ( new i = 0; i < TOTAL_TABLES; i++ ) {
        query = SQL_PrepareQuery( connect, tableSeed[i] )

        if ( !SQL_Execute( query ) ) {
            MySQL_Error( query, tableSeed[i], 1 )

            return false
        }

        SQL_FreeHandle( query )
    }

    log_amx( "[MySQL] Tables created successfuly" )

    return true
}
