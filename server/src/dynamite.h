#include "Box2D/Box2D.h"
#include "regresive_projectile.h"
#include "game_constants.h"

#ifndef __DYNAMITE_H__
#define __DYNAMITE_H__

class Dynamite : public RegresiveProjectile {
	public:
		Dynamite(b2World& world_entry, int number, float x, float y, int direction,
		GameConstants& info, std::map<int, Projectile*>& to_remove_e, MultipleProxy& proxy, unsigned int time);
		
		~Dynamite();
};

#endif
