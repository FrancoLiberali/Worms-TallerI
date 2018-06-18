#ifndef _BOOT_H
#define _BOOT_H

#include <map>
#include "SdlScreen.h"

class Boot {
private:
    SdlScreen screen;
    void loadConfigGame();
    void loadSprites();
    void loadImages();
    void loadWaterImage();
    void loadMenuWeapon();
    void loadSounds();
public:
    void init();
    SdlScreen& getScreen();    
};

#endif 