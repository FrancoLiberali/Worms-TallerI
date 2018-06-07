#include "Box2D/Box2D.h"
#include "fragment_projectile.h"
#include "projectile.h"
#include "little_projectile.h"
#include "game_constants.h"
#include <map>
#include "fragment_info.h"
#include "multiple_proxy.h"

#ifndef __MORTER_H__
#define __MORTER_H__

class Morter : public FragmentProjectile {
	public:
		Morter(b2World& world_entry, int number, float x, float y, float angle, int power, 
		GameConstants& info, std::map<int, Projectile*>& to_remove, std::vector<FragmentInfo*>& to_create_e,
		MultipleProxy& proxy);
		
		~Morter();
		
		virtual void update(int to_respect);
};

#endif