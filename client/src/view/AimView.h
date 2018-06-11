#ifndef _AIM_VIEW_H
#define _AIM_VIEW_H

#include "newView/SdlScreen.h"
#include "newView/TextureManager.h"

#include <math.h>

class AimView {
private:
    SdlScreen* screen; 
    float angle;
    bool show;
    int centerX, centerY;
public:
	AimView();
    void setCenter(int x, int y);
    void setScreen(SdlScreen* screen);
    void changeAngle(int delta);
    void changeDir();
	void draw();
    void enable();
    void disable();
};

#endif