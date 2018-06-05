#include "Box2D/Box2D.h"
#include "simple_projectile.h"

#ifndef __LITTLE_PROJECTILE_H__
#define __LITTLE_PROJECTILE_H__

class LittleProjectile : public SimpleProjectile {
	private:
		float x;
		float y;
		float angle;
		float vel;
	public:
		LittleProjectile(b2World& world_entry, int number, float x, float y, float angle, float vel, 
		int damage_e, int radius_e, std::map<int, Projectile*>& to_remove_e, MokProxy& proxy);
		
		~LittleProjectile();
};

#endif
