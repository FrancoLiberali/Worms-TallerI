#ifndef _WORM_CHANGE_LIFE_EVENT_H
#define _WORM_CHANGE_LIFE_EVENT_H

#include "Event.h"

/*@ class: WormChangeLifeEvent
* Evento de cambio de en la vida de un gusano.
*/
class WormChangeLifeEvent : public Event {
private:
	int idWorm;
    int newLife;
public:
	WormChangeLifeEvent(int id, int life);
	void process();
};

#endif