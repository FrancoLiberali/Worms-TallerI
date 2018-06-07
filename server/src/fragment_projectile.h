#include "Box2D/Box2D.h"
#include "projectile.h"
#include "little_projectile.h"
#include "fragment_info.h"

#ifndef __FRAGMENT_PROJECTILE_H__
#define __FRAGMENT_PROJECTILE_H__

class FragmentProjectile : public Projectile{
	private:
		unsigned int cant_fragments;
		int fragment_damage;
		int fragment_radius;
		int vel;
		std::vector<FragmentInfo*>& to_create;
		
	public:
		FragmentProjectile(b2World& world_entry, int number, float x, float y, float angle, float vel, 
		int damage_e, int radius_e, std::map<int, Projectile*>& to_remove_e, MultipleProxy& proxy,
		int fragment_damage_e, int fragment_radius_e, unsigned int cant_fragments, std::vector<FragmentInfo*>& to_create_e);
		
		~FragmentProjectile();
		
		virtual void update(int weapon);
		
		virtual void exploit();
};

#endif
