#ifndef _VIGA_VIEW_H_
#define _VIGA_VIEW_H_

#include "SdlScreen.h"
#include "TextureManager.h"

class VigaView {
private:
    int x;
    int y;
	int getXCenter();
	int getYCenter();
    SdlScreen& screen;
    Camera& camera;
    int angle;
public:
    VigaView(int posX, int posY, int angle, SdlScreen& screen, Camera& camera);
    ~VigaView();
    void draw();
};
#endif