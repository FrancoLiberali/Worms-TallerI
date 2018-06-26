#include "AimView.h"
#include "../common/Util.h"
#define RADIUS 50.0
#define PI 3.14159265
#define INIT 16

AimView::AimView(Camera& camera):show(false), posAngle(INIT),
     dir(-1), camera(camera){}


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
    Util::getDimentionTexture(aim, &w, &h);

    int posx = centerX + (int)(cos(currAngle*PI/180.0)*RADIUS) - w/2;
    int posy = centerY + (int)(sin(currAngle*PI/180.0)*RADIUS) - h/2;

    TextureManager::Instance().draw("aim", posx-camera.getX(), posy-camera.getY(),
            0, screen->getRenderer());
}

void AimView::enable(){
    show = true;
}

void AimView::disable(){
    show = false;
}

void AimView::reset(){
    posAngle = INIT;
}