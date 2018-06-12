#ifndef _AIM_VIEW_H
#define _AIM_VIEW_H

#include "newView/SdlScreen.h"
#include "newView/TextureManager.h"

#include <math.h>

class AimView {
private:
    SdlScreen* screen; 
    float angle;
    int posAngle = 17;
    int dir;
    bool show;
    int centerX, centerY;
    float  anglesRight[5] = {270,345,0,45,90};
    float anglesLeft[5] = { 270,225,180,135,90};

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