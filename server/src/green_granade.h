#include "Box2D/Box2D.h"
#include "regresive_projectile.h"
#include "game_constants.h"

#ifndef __GREEN_GRANADE_H__
#define __GREEN_GRANADE_H__

class GreenGranade : public RegresiveProjectile {
	public:
		GreenGranade(b2World& world_entry, int number, float x, float y, int direction, float angle, float power,
		GameConstants& info, std::vector<int>& to_remove_e, MultipleProxy& proxy, unsigned int time);
		
		~GreenGranade();
};

#endif
