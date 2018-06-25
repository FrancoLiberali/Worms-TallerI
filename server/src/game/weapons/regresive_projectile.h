#include "Box2D/Box2D.h"
#include "game/weapons/projectile.h"
#include <map>

#ifndef __REGRESIVE_PROJECTILE_H__
#define __REGRESIVE_PROJECTILE_H__

#define REGRESIVE_TYPE -1

class RegresiveProjectile : public Projectile{
	private:
		unsigned int time;
		
	public:
		// Crea un proyectil que explota luego de un determinado tiempo,
		// sin importar si tiene contactos antes.
		RegresiveProjectile(b2World& world_entry, int number, float x, float y, int direction, float angle, 
		float vel, int damage_e, int radius_e, std::vector<int>& to_remove_e, 
		MultipleProxy& proxy, unsigned int time);
		
		~RegresiveProjectile();
		
		// Actualiza el proyectil al paso de un frame de simulacion
		virtual void update(float wind);
};

#endif
