#include "Box2D/Box2D.h"
#include <map>
#include "proxy.h"
#include "projectile.h"
#include "little_projectile.h"
#include "game_constants.h"
#include "gusano.h"
#include "proxy.h"
#include "fake_proxy/mok_proxy.h"
#include "fragment_info.h"
#include <utility>

#ifndef __TURN_H__
#define __TURN_H__

class Turn{
	private:
		b2World& world;
		ProtectedQueue& queue;
		std::map<unsigned int, Gusano*>& gusanos;
		std::map<unsigned int, Gusano*>& to_remove_gusanos;
		GameConstants& info;
		//Proxy& proxy;
		MokProxy& proxy;
		const float time_step;
		const int velocity_iterations; 
		const int position_iterations;
		std::map<int, Projectile*> to_remove_projectiles;
		std::map<int, Projectile*> projectiles;
		int actual_max_projectile = 0;
		std::vector<FragmentInfo*> to_create;
		
		void gusano_move(char* msj, int active_number);
		void gusano_jump(char* msj, int active_number);
		void fire_weapon_sight_power(char* msj, int active_number);
		void fire_bazooka(char* msj, Gusano* gusano, int sight_angle, int power);
		void fire_morter(char* msj, Gusano* gusano, int sight_angle, int power);
		
	public:
		Turn(b2World& world_e, ProtectedQueue& queue_e, std::map<unsigned int, Gusano*>& gusanos_e, 
			std::map<unsigned int, Gusano*>& to_remove_gusanos_e, GameConstants& info_e, MokProxy& proxy_e);
		
		~Turn();
		
		void play(unsigned int gusano_number);
};

#endif
