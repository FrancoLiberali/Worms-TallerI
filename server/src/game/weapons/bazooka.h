#include "Box2D/Box2D.h"
#include "game/weapons/simple_projectile.h"
#include "game/weapons/projectile.h"
#include "game/game_constants.h"
#include "server/multiple_proxy.h"
#include <map>

#ifndef __BAZOOKA_H__
#define __BAZOOKA_H__

class Bazooka : public SimpleProjectile {
	public:
		// Crea un objeto bazooka que sale disparado.
		Bazooka(b2World& world_entry, int number, float x, float y, int direction, float angle, float power, 
		GameConstants& info, std::vector<int>& to_remove, MultipleProxy& proxy);
		
		~Bazooka();
		
		// Actualiza la trayectoria del proyectil al viento actual.
		virtual void update(float wind);
};

#endif
