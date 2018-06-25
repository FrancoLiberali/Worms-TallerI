#include "Box2D/Box2D.h"
#include "game/weapons/fragment_projectile.h"
#include "game/weapons/projectile.h"
#include "game/weapons/little_projectile.h"
#include "game/game_constants.h"
#include <map>
#include "game/weapons/fragment_info.h"
#include "server/multiple_proxy.h"

#ifndef __MORTER_H__
#define __MORTER_H__

class Morter : public FragmentProjectile {
	public:
		// Crea un objeto mortero que sale disparado.
		Morter(b2World& world_entry, int number, float x, float y, int direction, float angle, float power, 
		GameConstants& info, std::vector<int>& to_remove, std::vector<FragmentInfo>& to_create_e,
		MultipleProxy& proxy);
		
		~Morter();
		
		// Actualiza la trayectoria del proyectil al viento actual.
		virtual void update(float wind);
};

#endif
