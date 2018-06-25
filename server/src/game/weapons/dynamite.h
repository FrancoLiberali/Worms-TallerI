#include "Box2D/Box2D.h"
#include "game/weapons/regresive_projectile.h"
#include "game/game_constants.h"

#ifndef __DYNAMITE_H__
#define __DYNAMITE_H__

class Dynamite : public RegresiveProjectile {
	public:
		// Crea un objeto dinamita.
		Dynamite(b2World& world_entry, int number, float x, float y, int direction, float angle,
		GameConstants& info, std::vector<int>& to_remove_e, MultipleProxy& proxy, unsigned int time);
		
		~Dynamite();
};

#endif
