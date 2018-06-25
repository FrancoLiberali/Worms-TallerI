#ifndef _WIND_CHANGED_EVENT
#define _WIND_CHANGED_EVENT

#include "Event.h"

/*@ class: Event
* Evento de cambio de aire en el juego.
*/
class WindChangedEvent : public Event {
private:
	int windSpeed;
public:
	WindChangedEvent(int windSpeed);
	void process();
};

#endif