#include "Camera.h"
#include <stdio.h>

#define M_W 1200
#define M_H 1500

Camera::Camera(){
}

void Camera::setDimentionMap(int widht, int height){
    this->map_w = widht;
    this->map_h = height;
    /*this->map_h = M_H;
    this->map_w = M_H;*/
}


Camera::Camera(int w, int h) : w(w), h(h), map_h(0), map_w(0),
    vel(2), gap(10){}

int Camera::getX(){
    return centerX - w/2;
}

int Camera::getY(){
    return centerY - h/2;
}

void Camera::updateCenter(int x, int y){
    centerX = x;
    centerY = y;
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
        x_aux = this->centerX - vel;
    } else if (x > w - gap) {
        x_aux = this->centerX + vel;
    } else if (y < gap) {
        y_aux = this->centerY - vel;
    } else if (y > h - gap) {
        y_aux = this->centerY + vel;
    }

    bool limits = x_aux + w/2 < map_w && y_aux + h/2 < map_h;
    return limits;
}