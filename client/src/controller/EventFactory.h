#ifndef _EVENT_FACTORY
#define _EVENT_FACTORY 

#include "EventType.h"
#include "Event.h"
#include "../ProxyClient.h"
#include "../model/Model.h"
#include <sstream>

class EventFactory{
private:
	//static WeaponId getWeaponId(int id);
public:
	static Event* createEvent(const EventType& type, std::stringstream& ss, Model& model);
	static Event* createEvent(const EventType& type, ProxyClient& proxy, Model& model);
};
#endif