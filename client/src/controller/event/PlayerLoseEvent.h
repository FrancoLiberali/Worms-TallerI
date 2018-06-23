#ifndef _PLAYER_LOSE_EVENT
#define _PLAYER_LOSE_EVENT

#include "Event.h"

class PlayerLoseEvent : public Event {
private:
	int playerId;
public:
	PlayerLoseEvent(int idPlayer);
	void process();
};


#endif