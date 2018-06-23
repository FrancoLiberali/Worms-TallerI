#ifndef _CREATE_VIGA_EVENT_H
#define _CREATE_VIGA_EVENT_H

#include "Event.h"

class CreateVigaEvent : public Event {
private:
	int posx;
    int posy;
    int angle;
    mainView& view;
public:
	CreateVigaEvent(int x, int y, int angle, mainView& view);
	void process();
};

#endif