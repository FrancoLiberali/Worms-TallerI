#include "Box2D/Box2D.h"
#include "game/weapons/simple_projectile.h"

#ifndef __LITTLE_PROJECTILE_H__
#define __LITTLE_PROJECTILE_H__

class LittleProjectile : public SimpleProjectile {
	public:
		// Crea un objeto pequenio proyectil que sale disparado.
		LittleProjectile(b2World& world_entry, int number, float x, float y, int direction, float angle, float vel, 
		int damage_e, int radius_e, std::vector<int>& to_remove_e, MultipleProxy& proxy);
		
		~LittleProjectile();
};

#endif
