#ifndef _SECOND_EVENT
#define _SECOND_EVENT

#include "../../view/WormStateAndWeapon.h"
#include "Event.h"

/*@ class: Event
* Evento paso un segundo del juego.
*/
class SecondEvent : public Event {
public:
	SecondEvent();
	void process();
};


#endif