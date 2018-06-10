#ifndef _PLAYER_CONNECT_EVENT_H
#define _PLAYER_CONNECT_EVENT_H

#include "Event.h"

class PlayerConnectEvent : public Event {
private:
	int playerId;
    std::string name;
    Model& model;
public:
	PlayerConnectEvent(int id, std::string name, Model& model);
	void process();
};

#endif