#ifndef _BOOT_H
#define _BOOT_H

#include <map>
#include "SdlScreen.h"
/**
* @class Boot
* Inicializador de todos los recursas a usar
* Texturas, sonidos,fuentes
*/
class Boot {
private:
    SdlScreen screen;
    void loadSprites();
    void loadImages();
    void loadMenuWeapon();
    void loadSounds();
public:
    void init();
    SdlScreen& getScreen();    
};

#endif 