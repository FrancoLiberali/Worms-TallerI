#include "Box2D/Box2D.h"
#include "fragment_projectile.h"
#include "projectile.h"
#include "little_projectile.h"
#include "game_constants.h"

#ifndef __MORTER_H__
#define __MORTER_H__

class Morter : public FragmentProjectile {
	public:
		Morter(b2World& world_entry, float x, float y, float angle, GameConstants& info, std::vector<Projectile*>& to_remove, std::vector<LittleProjectile*>& to_create_e);
		
		~Morter();
};

#endif
