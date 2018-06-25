#ifndef _MISSILE_EXPLOTE_EVENT_H
#define _MISSILE_EXPLOTE_EVENT_H

#include "Event.h"
/*@ class: Event
* Evento que responde a la explosión de un misil que previamente fue creado.
*/
class MissileExploteEvent : public Event {
private:
	int idMissile;
public:
    MissileExploteEvent(int idMissile);
	void process();
};

#endif