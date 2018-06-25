#include "Box2D/Box2D.h"
#include "game/weapons/projectile.h"
#include "game/weapons/little_projectile.h"
#include "game/weapons/fragment_info.h"

#ifndef __FRAGMENT_PROJECTILE_H__
#define __FRAGMENT_PROJECTILE_H__

#define FRAGMENT_TYPE 0

class FragmentProjectile : public Projectile{
	private:
		const unsigned int cant_fragments;
		const int fragment_damage;
		const int fragment_radius;
		const int vel;
		std::vector<FragmentInfo>& to_create;
		
	public:
		// Crea un proyectil que al explotar expulsa fragmentos de proyectil
		FragmentProjectile(b2World& world_entry, int number, float x, float y, int direction, float angle, float vel, 
		int damage_e, int radius_e, std::vector<int>& to_remove_e, MultipleProxy& proxy,
		int fragment_damage_e, int fragment_radius_e, unsigned int cant_fragments, std::vector<FragmentInfo>& to_create_e);
		
		~FragmentProjectile();
		
		// Realiza la explosion basica de una proyectil
		// mas la creacion de fragmentos de proyectil que tambien explotan
		virtual void exploit();
};

#endif
