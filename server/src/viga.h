#include "Box2D/Box2D.h"
#include "multiple_proxy.h"

#ifndef __VIGA_H__
#define __VIGA_H__
class Viga{
	public:
		Viga(b2World& world_entry, float x, float y, float angle, MultipleProxy& proxy);
		
		~Viga();		
};

#endif
