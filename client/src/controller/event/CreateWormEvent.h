#ifndef _CREATE_WORM_EVENT_H
#define _CREATE_WORM_EVENT_H

#include "Event.h"

/*@class: CreateWormEvent
* Evento que responde a la creación de un worm del server
*/
class CreateWormEvent : public Event {
private:
    int idWorm;
    int idOwner;
	int posx;
    int posy;
    int dir;
    int angle;
public:
	CreateWormEvent(int idWorm, int idOwner, int x, int y, int dir , int angle);
	void process();
};

#endif