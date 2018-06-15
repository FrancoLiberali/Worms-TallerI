#include "Box2D/Box2D.h"
#include "projectile.h"
#include <map>

#ifndef __REGRESIVE_PROJECTILE_H__
#define __REGRESIVE_PROJECTILE_H__

class RegresiveProjectile : public Projectile{
	private:
		unsigned int time;
		
	public:
		RegresiveProjectile(b2World& world_entry, int number, float x, float y, int direction, float angle, 
		float vel, int damage_e, int radius_e, std::map<int, Projectile*>& to_remove_e, 
		MultipleProxy& proxy, unsigned int time);
		
		~RegresiveProjectile();
		
		virtual void update();
};

#endif
