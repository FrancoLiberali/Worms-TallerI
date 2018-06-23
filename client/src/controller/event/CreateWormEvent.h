#ifndef _CREATE_WORM_EVENT_H
#define _CREATE_WORM_EVENT_H

#include "Event.h"

class CreateWormEvent : public Event {
private:
    int idWorm;
    int idOwner;
	int posx;
    int posy;
    int dir;
    int angle;
    Model& model;
    mainView& view;
public:
	CreateWormEvent(int idWorm, int idOwner, int x, int y, int dir ,
                     int angle, Model&model, mainView& view);
	void process();
};

#endif