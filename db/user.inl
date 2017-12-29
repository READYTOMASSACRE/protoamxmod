/**
 * Авторизация пользователя
 *
 * @param int index - индекс игрока
 * @param string[] login - логин пользователя
 * @param string[] password - пароль пользователя
 */
bool:User_Login( index, const login[], const password[] ) {

    if ( User_IsAlreadyLogged( index ) ) return true

    new md5buffer[34], salted[32] = USER_SALT, queryStr[512], Trie:result

    strcat(salted, password, 31)
    md5 (salted, md5buffer)

    format (queryStr, 511, "SELECT * FROM `users` WHERE login=%s AND PASSWORD=%s;", login, md5buffer)

    result = MySQL_Query( MySQL_Connect, queryStr )

    new outputLogin[32], kills, death, ratio
    TrieGetString(result, "login", outputLogin, 31)

    if ( !output ) return false

    TrieGetCell(result, "kills", kills)
    TrieGetCell(result, "death", death)
    TrieGetCell(result, "ratio", ratio)


    UserLogged[ index ][ loginState ] = true
    UserLogged[ index ][ login ] = outputLogin
    UserLogged[ index ][ kills ] = kills
    UserLogged[ index ][ death ] = death
    UserLogged[ index ][ ratio ] = ratio

    return true
}

bool:User_Register( index, const login[], const password[], const email[]) {

    /*if ( !login || !password ) Proto_Notice(PROTO_ERROR, PROTO_INVALID_FIELDS)*/

    new md5buffer[34], salted[32] = USER_SALT, queryStr[512], Trie:result

    strcat(salted, password, 31)
    md5 (salted, md5buffer)

    format (queryStr, 511, "INSERT INTO users SET `login`='%s', `password`='%s', `email`='%s';", login, password, email)

    result = MySQL_Query(MySQL_Connect, queryStr)

    new outputLogin[32], kills, death, ratio
    TrieGetString(result, "login", outputLogin, 31)

    if ( !output ) return false

    TrieGetCell(result, "kills", kills)
    TrieGetCell(result, "death", death)
    TrieGetCell(result, "ratio", ratio)


    UserLogged[ index ][ loginState ] = true
    UserLogged[ index ][ login ] = outputLogin
    UserLogged[ index ][ kills ] = kills
    UserLogged[ index ][ death ] = death
    UserLogged[ index ][ ratio ] = ratio

    return true
}
