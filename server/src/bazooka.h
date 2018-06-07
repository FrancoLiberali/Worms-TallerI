#include "Box2D/Box2D.h"
#include "simple_projectile.h"
#include "projectile.h"
#include "game_constants.h"
#include "multiple_proxy.h"
#include <map>

#ifndef __BAZOOKA_H__
#define __BAZOOKA_H__

class Bazooka : public SimpleProjectile {
	public:
		Bazooka(b2World& world_entry, int number, float x, float y, float angle, int power, 
		GameConstants& info, std::map<int, Projectile*>& to_remove, MultipleProxy& proxy);
		
		~Bazooka();
		
		virtual void update(int to_respect);
};

#endif
