#ifndef _BOOT_H
#define _BOOT_H

#include <map>
#include "../view/SdlScreen.h"
/**
* @class Boot
* Inicializador de todos los recursas a usar
* Texturas, sonidos,fuentes
*/
class Boot {
private:
    SdlScreen screen;
    //carga los sprites e imagenes
    void loadSprites();
    //carga los iconos de las armas
    void loadMenuWeapon();
    //carga todos los sonidos y musicas
    void loadSounds();
    //carga todas las fuentes
    void loadFonts();
public:
    //Inicializador, carga todos los recursos
    void init();
    SdlScreen& getScreen();    
};

#endif 