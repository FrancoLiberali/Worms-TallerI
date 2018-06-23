#include "Box2D/Box2D.h"
#include "regresive_projectile.h"
#include "fragment_projectile.h"
#include "game_constants.h"

#ifndef __RED_GRANADE_H__
#define __RED_GRANADE_H__

class RedGranade : public RegresiveProjectile {
	private:
		GameConstants& info;
		std::vector<FragmentInfo>& to_create;
	public:
		RedGranade(b2World& world_entry, int number, float x, float y, int direction, float angle, float power,
		GameConstants& info, std::vector<int>& to_remove_e, std::vector<FragmentInfo>& to_create_e, 
		MultipleProxy& proxy, unsigned int time);
		
		~RedGranade();
		
		virtual void exploit();
};
#endif
