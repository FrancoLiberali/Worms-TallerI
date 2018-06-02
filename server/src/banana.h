#include "Box2D/Box2D.h"
#include "regresive_projectile.h"
#include "game_constants.h"

#ifndef __BANANA_H__
#define __BANANA_H__

class Banana : public RegresiveProjectile {
	public:
		Banana(b2World& world_entry, float x, float y, float angle, GameConstants& info, std::vector<Projectile*>& to_remove_e, unsigned int time);
		
		~Banana();
};

#endif
