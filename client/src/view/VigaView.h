#ifndef _VIGA_VIEW_H_
#define _VIGA_VIEW_H_

#include "newView/SdlScreen.h"
#include "newView/TextureManager.h"

class VigaView {
private:
    int x;
    int y;
	int getXCenter();
	int getYCenter();
    SdlScreen& screen;
    int angle;
public:
    VigaView(int posX, int posY, int angle, SdlScreen& screen);
    ~VigaView();
    void draw();
};
#endif