#include "Box2D/Box2D.h"
#include "simple_projectile.h"
#include "game_constants.h"

#ifndef __GREEN_GRANADE_H__
#define __GREEN_GRANADE_H__

class GreenGranade : public SimpleProjectile {
	public:
		GreenGranade(b2World& world_entry, float x, float y, float angle, GameConstants& info, std::vector<Projectile*>& to_remove_e);
		
		~GreenGranade();
};

#endif
