#include "Box2D/Box2D.h"

#ifndef __VIGA_H__
#define __VIGA_H__
class Viga{
	public:
		Viga(b2World& world_entry, float x, float y, float angle);
		
		~Viga();		
};

#endif
