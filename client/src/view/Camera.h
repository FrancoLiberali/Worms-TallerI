#ifndef _CAMERA_H
#define _CAMERA_H

class Camera {
private:
    int centerX, centerY;
    int w, h;
public:
    Camera();
    void setDimension(int w, int h);
    int getX();
    int getY();
    void updateCenter(int x, int y);
    void focusCenterWindow();
};

#endif