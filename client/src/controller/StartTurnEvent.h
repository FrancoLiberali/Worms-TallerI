#ifndef _START_TURN_EVENT
#define _START_TURN_EVENT

#include "Event.h"

class StartTurnEvent : public Event {
private:
	int playerId;
    int idWorm;
    Model& model;
    mainView& view;
public:
	StartTurnEvent(int idPlayer, int idWorm, Model& model, mainView& view);
	void process();
};


#endif