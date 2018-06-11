#include "AimView.h"
#include <iostream>

#define RADIUS 80
#define PI 3.14159265

AimView::AimView():show(false), angle(0){
}


void AimView::setCenter(int x, int y){
    centerX = x;
    centerY = y;
}

void AimView::setScreen(SdlScreen* screen){
    this->screen = screen;
}

void AimView::changeAngle(int delta){
    angle += ((delta == 1) ? 5,6 : -5.6);
}

void AimView::changeDir(){
    std::cout<<"Aim change dir"<<std::endl;
    if (angle > 0.0 && angle < 90.0)
        angle = 180.0 - angle;
    else if (angle > 90 && angle <180)
        angle = 180 - angle;
    else if (angle > 180 && angle < 270)
        angle = 540 - angle;
    else if (angle > 270)
        angle = 540 - angle;
    draw();
}

void AimView::draw(){
    if  (!show)
        return;
    int posx = centerX + (int)cos(angle*PI/180)*RADIUS;
    int posy = centerY + (int)sin(angle*PI/180)*RADIUS;
    TextureManager::Instance().draw("aim", posx, posy, 0, screen->getRenderer());
}

void AimView::enable(){
    show = true;
}

void AimView::disable(){
    show = false;
}