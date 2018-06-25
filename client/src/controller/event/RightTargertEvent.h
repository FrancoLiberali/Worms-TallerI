#ifndef _RIGHT_TARGET_EVENT
#define _RIGHT_TARGET_EVENT

#include "../../view/WormStateAndWeapon.h"
#include "Event.h"

/*@ class: Event
* Evento, el objetivo elegido para realizar una acción teledirigida es correcta.
*/
class RightTargertEvent : public Event {
private:
	WeaponId idWeapon;
public:
	RightTargertEvent(int idWeapon);
	void process();
};


#endif