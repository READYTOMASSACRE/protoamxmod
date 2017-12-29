
new const USER_SALT[] = "!X@bg8&bl"

enum UserStats
{
    loginState,
    login,
    kill,
    death,
    ratio
}

new UserInfo[ MAX_PLAYERS ][ UserStats ]

forward bool:User_Login( index, const login[], const password[] )
forward bool:User_Logout( const username[] )
