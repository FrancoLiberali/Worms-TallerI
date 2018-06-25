#include "Box2D/Box2D.h"
#include "game/weapons/regresive_projectile.h"
#include "game/game_constants.h"
#include "server/multiple_proxy.h"

#ifndef __BANANA_H__
#define __BANANA_H__

class Banana : public RegresiveProjectile {
	public:
		// Crea un objeto banana que sale disparado.
		Banana(b2World& world_entry, int number, float x, float y, int direction, float angle, float power,
		GameConstants& info, std::vector<int>& to_remove_e, MultipleProxy& proxy, unsigned int time);
		
		~Banana();
};

#endif
