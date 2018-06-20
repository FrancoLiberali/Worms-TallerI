#ifndef _CREATE_STAGE_EVENT_H
#define _CREATE_STAGE_EVENT_H

#include "Event.h"

class CreateStageEvent : public Event {
private:
	int widht;
    int height;
public:
	CreateStageEvent(int widht, int height);
	void process();
};

#endif