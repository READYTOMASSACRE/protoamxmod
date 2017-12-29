/**
 * Файл с настройками
 */

/**
 * CVARS для соединения с бд
 */
new Cvar_proto_mysql_dbhost
new Cvar_proto_mysql_dbuser
new Cvar_proto_mysql_dbpass
new Cvar_proto_mysql_dbname

Cvar_Init() {

    /**
     * CvarS для соединения с бд
     */
    Cvar_proto_mysql_dbhost             = register_cvar( "proto_mysql_dbhost"           , "127.0.0.1"                   )
    Cvar_proto_mysql_dbuser             = register_cvar( "proto_mysql_dbuser"           , "root"                        )
    Cvar_proto_mysql_dbpass             = register_cvar( "proto_mysql_dbpass"           , "root"                        )
    Cvar_proto_mysql_dbname             = register_cvar( "proto_mysql_dbname"           , "cstrike"                     )
}
