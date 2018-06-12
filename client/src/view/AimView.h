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
    float  angles[32] = {-90, -84, -78,-72,-66,-60,-54,-48,-42,-36,-30,-24,-18,-12,-6,0,
                    5.8,11.6,17.4,23.2,29,34.8,40.6,46.4,52.2,58,63.8,69.6,75.4,81.2,90};

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