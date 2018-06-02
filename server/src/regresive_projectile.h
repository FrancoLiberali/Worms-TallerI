#include "Box2D/Box2D.h"
#include "projectile.h"

#ifndef __REGRESIVE_PROJECTILE_H__
#define __REGRESIVE_PROJECTILE_H__

class RegresiveProjectile : public Projectile{
	private:
		unsigned int time;
		
	public:
		RegresiveProjectile(b2World& world_entry, float x, float y, float angle, 
		float vel, int damage_e, int radius_e, std::vector<Projectile*>& to_remove_e, unsigned int time);
		
		~RegresiveProjectile();
		
		virtual void update();
};

#endif
