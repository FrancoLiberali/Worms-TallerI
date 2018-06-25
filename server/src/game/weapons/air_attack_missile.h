#include "Box2D/Box2D.h"
#include "game/weapons/simple_projectile.h"
#include "game/weapons/projectile.h"
#include "game/game_constants.h"
#include "server/multiple_proxy.h"

#ifndef __AIR_ATTACK_MISSILE_H__
#define __AIR_ATTACK_MISSILE_H__

class AirAttackMissile : public SimpleProjectile {
	public:
		// Crea uno de los misiles de un ataque aereo
		AirAttackMissile(b2World& world_entry, int number, float x, GameConstants& info, 
							std::vector<int>& to_remove, MultipleProxy& proxy);
		
		~AirAttackMissile();
		
		// Actualiza la trayectoria del proyectil al viento actual.
		virtual void update(float wind);
};

#endif
