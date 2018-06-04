#include "Box2D/Box2D.h"
#include <map>
#include "proxy.h"
#include "projectile.h"
#include "little_projectile.h"
#include "game_constants.h"
#include "gusano.h"

#ifndef __TURN_H__
#define __TURN_H__

class Turn{
	private:
		b2World& world;
		ProtectedQueue& queue;
		std::map<unsigned int, Gusano*>& gusanos;
		std::map<unsigned int, Gusano*>& to_remove_gusanos;
		GameConstants& info;
		const float time_step;
		const int velocity_iterations; 
		const int position_iterations;
		std::vector<Projectile*> to_remove;
		std::vector<LittleProjectile*> to_create;
		std::vector<Projectile*> projectiles;
		
	public:
		Turn(b2World& world_e, ProtectedQueue& queue_e, std::map<unsigned int, Gusano*>& gusanos_e, 
			std::map<unsigned int, Gusano*>& to_remove_gusanos_e, GameConstants& info_e);
		
		~Turn();
		
		void play(unsigned int gusano_number);
};

#endif
