#ifndef _PLAYER_OFF_EVENT
#define _PLAYER_OFF_EVENT

#include "Event.h"

class PlayerOffEvent : public Event {
private:
	int playerId;
    Model& model;
    mainView& view;
public:
	PlayerOffEvent(int idPlayer, Model& model, mainView& view);
	void process();
};


#endif