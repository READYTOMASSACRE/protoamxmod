/**
 * PROTO (mod)
 *
 * by Rage Cacao
 */

/* File location: $moddir/addons/amxmodx/plugins/proto.amxx */

#define MAX_PLAYERS             32 + 1

#include <amxmodx>
#include <sqlx>
#include <celltrie>

#include "proto/version.h"
#include "proto/cvar.inl"
#include "proto/db/mysql.h"
#include "proto/db/mysql.inl"
#include "proto/db/user.h"
#include "proto/db/user.inl"
#include "proto/auth.h"
#include "proto/auth.inl"

/**
 * Handle when server restart / change map
 */
public plugin_init() {
    register_plugin(PROTO_PLUGIN_NAME, PROTO_VERSION_STR, PROTO_AUTHOR)

    register_dictionary("proto.txt")
    log_amx("Running %s, current version: %s, author: %s", PROTO_PLUGIN_NAME, PROTO_VERSION_STR, PROTO_AUTHOR)

    Cvar_Init()
    MySQL_Init(MySQL_Connect, MySQL_Tuple)

    Auth_MenuInit()
    register_clcmd("proto_auth", "Auth", -1, "[PROTO] Авторизация на сервере")
}
