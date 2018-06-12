#include "Camera.h"

Camera::Camera(){
}

void Camera::setDimension(int w, int h){
    this->w = w;
    this->h = h;
}

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