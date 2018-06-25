#include "Box2D/Box2D.h"
#include "server/multiple_proxy.h"

#ifndef __VIGA_H__
#define __VIGA_H__
class Viga{
	public:
		// Crea una viga grande si big = true y pequenia de lo contrario.
		Viga(b2World& world_entry, float x, float y, float angle, MultipleProxy& proxy, bool big);
		
		~Viga();		
};

#endif
