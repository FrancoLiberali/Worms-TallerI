#include "Box2D/Box2D.h"
#include "projectile.h"
#include "fake_proxy/mok_proxy.h"

#ifndef __SIMPLE_PROJECTILE_H__
#define __SIMPLE_PROJECTILE_H__

class SimpleProjectile : public Projectile{
	public:		
		SimpleProjectile(b2World& world_entry, int number, float x, float y, float angle, float vel, 
		int damage_e, int radius_e, std::map<int, Projectile*>& to_remove, MultipleProxy& proxy);
		
		~SimpleProjectile();
		
		virtual void update();
};

#endif
