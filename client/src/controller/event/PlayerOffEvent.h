#ifndef _PLAYER_OFF_EVENT
#define _PLAYER_OFF_EVENT

#include "Event.h"

/*@ class: Event
* Evento creado a partir de que un jugador se desconecto.
*/
class PlayerOffEvent : public Event {
private:
	int playerId;
public:
	PlayerOffEvent(int idPlayer);
	void process();
};


#endif