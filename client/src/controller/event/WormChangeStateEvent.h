#ifndef _WORM_CHANGE_STATE_EVENT
#define _WORM_CHANGE_STATE_EVENT

#include "Event.h"
#include "../../view/WormStateAndWeapon.h"

/*@class: WormChangeStateEvent
* Evento de cambio de estado de un gusano. El estado es un estado válido.
*/
class WormChangeStateEvent : public Event {
private:
	int wormID;
	WormState newState;
public:
	WormChangeStateEvent(int id, int state);
	void process();
};

#endif