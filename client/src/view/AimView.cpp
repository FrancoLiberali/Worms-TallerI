#include "AimView.h"
#include <iostream>

#define RADIUS 50
#define PI 3.14159265
#define VAR

AimView::AimView():show(false), posAngle(16), dir(-1){
}


void AimView::setCenter(int x, int y){
    centerX = x;
    centerY = y;
}

void AimView::setScreen(SdlScreen* screen){
    this->screen = screen;
}

void AimView::changeAngle(int delta){
    if (posAngle == 31 || posAngle == 0)
        return;
    posAngle += delta;
}

void AimView::changeDir(){
    dir = -dir;
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