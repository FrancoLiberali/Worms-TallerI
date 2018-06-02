#include "Box2D/Box2D.h"
#include "simple_projectile.h"
#include "projectile.h"
#include "game_constants.h"

#ifndef __BAZOOKA_H__
#define __BAZOOKA_H__

class Bazooka : public SimpleProjectile {
	public:
		Bazooka(b2World& world_entry, float x, float y, float angle, GameConstants& info, std::vector<Projectile*>& to_remove);
		
		~Bazooka();
};

#endif
