#ifndef _START_TURN_EVENT
#define _START_TURN_EVENT

#include "Event.h"

/*@ class: Event
* Evento de comienzo de turno.
*/
class StartTurnEvent : public Event {
private:
	int playerId;
    int idWorm;
public:
	StartTurnEvent(int idPlayer, int idWorm);
	void process();
};


#endif