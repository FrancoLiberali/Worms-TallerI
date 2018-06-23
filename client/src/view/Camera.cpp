#include "Camera.h"
#include <stdio.h>

#define M_W 1200
#define M_H 1500

Camera::Camera(){
}

void Camera::setDimentionMap(int widht, int height){
    this->map_w = widht;
    this->map_h = height;
}


Camera::Camera(int w, int h) : w(w), h(h), map_h(0), map_w(0),
    vel(5), gap(10){}

int Camera::getX(){
    return centerX - w/2;
}

int Camera::getY(){
    return centerY - h/2;
}

void Camera::updateCenter(int x, int y){

    if (x + w/2 >= map_w)
        return;
    if (x - w/2 <= 0)
        centerX = w/2;
    else{
        centerX = x;
    }
    if (y + h/2 >= map_h)
        return;
    if (y - h/2 <=0)
        centerY = h/2;
    else{
        centerY = y;
    }
}

void Camera::focusCenterWindow(){
    updateCenter(w/2, h/2);
}

void Camera::move(int x, int y){
    if (x < gap) {
        this->centerX -= vel;
    } else if (x > w - gap) {
        this->centerX += vel;
    } else if (y < gap) {
        this->centerY -= vel;
    } else if (y > h - gap) {;
        this->centerY += vel;
    }
}

bool Camera::inLimits(int x, int y){
    int x_aux = 0;
    int y_aux = 0;

    if (x < gap) {
        x_aux = this->centerX - w/2 - vel;
    } else if (x > w - gap) {
        x_aux = this->centerX + vel;
    } else if (y < gap) {
        y_aux = this->centerY - h/2 - vel;
    } else if (y > h - gap) {
        y_aux = this->centerY + vel;
    }

    bool limits = x_aux >= 0 && y_aux >= 0 && 
                x_aux + w/2 < map_w && y_aux + h/2 < map_h;
    return limits;
}