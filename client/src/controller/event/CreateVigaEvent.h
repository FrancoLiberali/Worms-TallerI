#ifndef _CREATE_VIGA_EVENT_H
#define _CREATE_VIGA_EVENT_H

#include "Event.h"

/*@class: CreateVigaEvent
* Evento que responde a la creación de una viga del server
*/
class CreateVigaEvent : public Event {
private:
	int posx;
    int posy;
    int angle;
public:
	CreateVigaEvent(int x, int y, int angle);
	void process();
};

#endif