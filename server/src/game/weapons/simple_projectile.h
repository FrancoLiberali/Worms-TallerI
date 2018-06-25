#include "Box2D/Box2D.h"
#include "game/weapons/projectile.h"

#ifndef __SIMPLE_PROJECTILE_H__
#define __SIMPLE_PROJECTILE_H__

#define SIMPLE_TYPE 0

class SimpleProjectile : public Projectile{
	public:		
		// Crea un proyectil que explota cuando tiene un contacto con otro objeto.
		SimpleProjectile(b2World& world_entry, int number, float x, float y, int direction, float angle, float vel, 
		int damage_e, int radius_e, std::vector<int>& to_remove, MultipleProxy& proxy);
		
		~SimpleProjectile();
};

#endif
