#include "AimView.h"
#include <iostream>

#define RADIUS 50
#define PI 3.14159265
#define VAR 5.6

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
    if (posAngle == 31 && delta > 0)
        return;
    if (posAngle == 0 && delta < 0)
        return;
    posAngle += delta;
    draw();
}

void AimView::changeDir(){
    dir = -dir;
    draw();
}

void AimView::draw(){
    if  (!show)
        return;
    float currAngle = 0;
    if (dir == -1)
        currAngle =  anglesLeft[posAngle];
    else
        currAngle = anglesRight[posAngle];

    SDL_Texture* aim  = TextureManager::Instance().getTexture("aim");
    int w, h;
    SDL_QueryTexture(aim,NULL,NULL, &w, &h);

    int posx = ((int)(cos(currAngle*PI/180)*1000*RADIUS))/1000;
    int posy = ((int)(sin(currAngle*PI/180)*1000*RADIUS)/1000);
    TextureManager::Instance().draw("aim", posx, posy, 0, screen->getRenderer());
}

void AimView::enable(){
    show = true;
}

void AimView::disable(){
    show = false;
}