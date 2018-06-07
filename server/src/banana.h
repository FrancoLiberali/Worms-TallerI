#include "Box2D/Box2D.h"
#include "regresive_projectile.h"
#include "game_constants.h"
#include "multiple_proxy.h"

#ifndef __BANANA_H__
#define __BANANA_H__

class Banana : public RegresiveProjectile {
	public:
		Banana(b2World& world_entry, int number, float x, float y, float angle, GameConstants& info, 
		std::map<int, Projectile*>& to_remove_e, MultipleProxy& proxy, unsigned int time);
		
		~Banana();
};

#endif
