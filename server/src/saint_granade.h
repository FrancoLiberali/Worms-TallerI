#include "Box2D/Box2D.h"
#include "regresive_projectile.h"
#include "game_constants.h"

#ifndef __SAINT_GRANADE_H__
#define __SAINT_GRANADE_H__

class SaintGranade : public RegresiveProjectile {
	public:
		SaintGranade(b2World& world_entry, int number, float x, float y, int direction, float angle, float power,
		GameConstants& info, std::map<int, Projectile*>& to_remove_e, MultipleProxy& proxy, unsigned int time);
		
		~SaintGranade();
};

#endif
