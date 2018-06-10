#ifndef _PLAYER_ID_EVENT
#define _PLAYER_ID_EVENT

#include "Event.h"

class PlayerIdEvent : public Event {
private:
	int playerId;
    Model& model;
    ProxyClient& proxy;
public:
	PlayerIdEvent(int id, Model& model, ProxyClient& proxy);
	void process();
};

#endif