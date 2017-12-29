/**
 * Головной файл MySQL
 */

#define MYSQL_ERR_TIMEOUT 2006
#define TOTAL_TABLES 1

/**
 * variables
 */
new const tableSeed[TOTAL_TABLES][] =
{
    "CREATE TABLE IF NOT EXISTS `users` ( \
        id int unsigned auto_increment primary key, \
        login varchar(32) not null unique, \
        email varchar(32) default null unique, \
        password varchar(128) not null, \
        created timestamp default current_timestamp, \
        kills int default 0, \
        death int default 0, \
        ratio float default 0, \
        index login_idx (login) \
    );"
}
new Handle:MySQL_Connect
new Handle:MySQL_Tuple
new bool:MySQL_connectionState = false

/**
 * forwards
 */
forward bool:MySQL_Init( &Handle:connect, &Handle:tuple );
forward bool:MySQL_Close( &Handle:connect, &Handle:tuple );
forward bool:MySQL_Error( Handle:query, queryString[], id );
forward bool:MySQL_IsConnected();
forward bool:MySQL_CreateTables( Handle:connect );
forward Trie:MySQL_Query( Handle:connect, queryString[] );
forward Trie:MySQL_Parse( Handle:query, &Trie:result );

/**
 * stocks
 */
