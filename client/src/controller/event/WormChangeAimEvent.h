#ifndef _WORM_CHANGE_AIM_EVENT
#define _WORM_CHANGE_AIM_EVENT

#include "Event.h"

/*@ class: WormChangeAimEvent
* Evento de cambio de mira en el arma del gusano.
*/
class WormChangeAimEvent : public Event {
private:
    int delta;
public:
	WormChangeAimEvent(int delta);
	void process();
};

#endif