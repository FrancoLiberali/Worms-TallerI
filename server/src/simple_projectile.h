#include "Box2D/Box2D.h"
#include "projectile.h"

#ifndef __SIMPLE_PROJECTILE_H__
#define __SIMPLE_PROJECTILE_H__

class SimpleProjectile : public Projectile{
	protected:
		void create(float x, float y, float angle, float vel);
	
	public:
		SimpleProjectile(b2World& world_entry, int damage_e, int radius_e, std::vector<Projectile*>& to_remove);
		
		SimpleProjectile(b2World& world_entry, float x, float y, float angle, float vel, int damage_e, int radius_e, std::vector<Projectile*>& to_remove);
		
		~SimpleProjectile();
		
		virtual void update();
};

#endif
