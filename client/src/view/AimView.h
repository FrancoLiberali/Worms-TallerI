#ifndef _AIM_VIEW_H
#define _AIM_VIEW_H

#include "SdlScreen.h"
#include "TextureManager.h"

#include <math.h>

class AimView {
private:
    SdlScreen* screen; 
    Camera& camera;
    float angle;
    int posAngle = 17;
    int dir;
    bool show;
    int centerX, centerY;
    float  anglesRight[32] = {90,84.4,78.8,73.2,67.6,62,56.4,50.8,45.2,39.6,34,28.4,22.8,17.2,11.6,6,0,
                            354,348,342,336,330,324,318,312,306,300,294,288,282,276,270};
    float anglesLeft[32] = { 90,95.7,101.4,107.1,112.8,118.5,124.2,129.9,135.6,141.3,147,152.7,158.4,164.1,169.8,175.5,180,
                            186,192,198,204,210,216,222,228,234,240,246,252,258,264,270};

public:
	AimView(Camera& camera);
    void setCenter(int x, int y);
    void setScreen(SdlScreen* screen);
    void changeAngle(int delta);
    void changeDir();
	void draw();
    void enable();
    void disable();
    void reset();
};

#endif