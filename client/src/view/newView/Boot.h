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
    void loadEart();
    void loadMenuWeapon();
    void initCamera(int w, int h);
    void realoadEart();
public:
    void init(std::string player);
    void reinit();
    SdlScreen& getScreen();    
};

#endif 