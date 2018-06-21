#include "Box2D/Box2D.h"
#include "simple_projectile.h"
#include "projectile.h"
#include "game_constants.h"
#include "multiple_proxy.h"
#include <map>

#ifndef __AIR_ATTACK_MISSILE_H__
#define __AIR_ATTACK_MISSILE_H__

class AirAttackMissile : public SimpleProjectile {
	public:
		AirAttackMissile(b2World& world_entry, int number, float x, GameConstants& info, 
							std::map<int, Projectile*>& to_remove, MultipleProxy& proxy);
		
		~AirAttackMissile();
};

#endif
