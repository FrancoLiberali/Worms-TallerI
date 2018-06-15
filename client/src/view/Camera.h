#ifndef _CAMERA_H
#define _CAMERA_H

class Camera {
private:
    int centerX, centerY;
    int w, h;
    int map_w, map_h;
    int dirX;
    int dirY;
    int vel;
    int gap;
public:
    Camera();
    void setDimension(int w, int h);
    int getX();
    int getY();
    void updateCenter(int x, int y);
    void focusCenterWindow();
    void move(int x, int y);
    bool inLimits(int x, int y);
};

#endif