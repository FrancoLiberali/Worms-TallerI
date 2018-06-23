#ifndef _CAMERA_MOVE_EVENT_H
#define _CAMERA_MOVE_EVENT_H

#include "Event.h"

class CameraMoveEvent : public Event {
private:
    int x;
    int y;
public:
    CameraMoveEvent(int x, int y);
    void process();
};

#endif
