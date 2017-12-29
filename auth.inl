/**
 * Авторизация на сервере
 */

/**
 * Производит авторизацию
 */
public Auth(index) {
    menu_display(index, AuthMenu)

    return PLUGIN_HANDLED
}

public Auth_MenuHandler( id, menu, item ) {
    return PLUGIN_HANDLED
}

Auth_MenuInit() {

    new MenuItemName[64]
    formatex(MenuItemName, charsmax(MenuItemName), "%L", LANG_PLAYER, "USER_MENU_AUTH")
    AuthMenu = menu_create(MenuItemName, "Auth_MenuHandler")

    menu_additem(AuthMenu, "\bAuth")
    menu_additem(AuthMenu, "^4Reg ^3[New]", "Register", 0, -1)
    menu_addtext(AuthMenu, "text info", 1)
}
