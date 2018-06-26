#ifndef _EVENT_FACTORY
#define _EVENT_FACTORY 

#include "EventType.h"
#include "event/Event.h"
#include "../ProxyClient.h"
#include "../model/Model.h"
#include <string>

/*@class: EventFactory
* Usa el patrón factory para generar los eventos, cada evento se corresponde con un mensaje
* del servidor. Los eventos son encolados en el EventHandler.
*/
class EventFactory{
public:
	static Event* createEvent(const EventType& type, ProxyClient& proxy);
};
#endif