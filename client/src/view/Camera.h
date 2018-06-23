#ifndef _CAMERA_H
#define _CAMERA_H

/**
 * @class Camera
 * Camara del juego, enfoca la parte del mapa que indique el jugador.
 * cada vez que se dibuja por defecto al worm en turno
 */
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
    Camera(int w, int h);
    void setDimentionMap(int widht, int height);
    int getX();
    int getY();
    void updateCenter(int x, int y);
    void focusCenterWindow();
    void move(int x, int y);
    bool inLimits(int x, int y);
};

#endif