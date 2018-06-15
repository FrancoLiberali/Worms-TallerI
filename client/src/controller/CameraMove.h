#ifndef _CAMERA_MOVE_H
#define _CAMERA_MOVE_H

#include "Event.h"

class CameraMove : public Event {
private:
    int x;
    int y;
public:
    CameraMove(int x, int y);
    void process();
};

#endif
