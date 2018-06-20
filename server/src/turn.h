#include "Box2D/Box2D.h"
#include <map>
#include "proxy.h"
#include "projectile.h"
#include "little_projectile.h"
#include "game_constants.h"
#include "gusano.h"
#include "multiple_proxy.h"
#include "fake_proxy/mok_proxy.h"
#include "fragment_info.h"
#include <utility>

#ifndef __TURN_H__
#define __TURN_H__

class Turn{
	private:
		b2World& world;
		ProtectedQueue& queue;
		std::map<int, std::map<int, Gusano*>>& players;
		std::vector<std::pair<int, int>>& to_remove_gusanos;
		GameConstants& info;
		MultipleProxy& proxy;
		std::map<int, std::vector<int>> ammunition;
		const float time_step;
		const int velocity_iterations; 
		const int position_iterations;
		std::map<int, Projectile*> to_remove_projectiles;
		std::map<int, Projectile*> projectiles;
		int actual_max_projectile = 0;
		std::vector<FragmentInfo*> to_create;
		int weapon = 0;
		float sight_angle = 0;
		int regresive_time = 5;
		float power = 1;
		bool fired;
		
		void disconnect(int player_id, int active_player, int& turn_actual_len);
		void gusano_move(char* msj, Gusano* gusano);
		void gusano_jump(char* msj, Gusano* gusano);
		void gusano_back_jump(char* msj, Gusano* gusano);
		void take_weapon(int player_id, char* msj);
		void changeSightAngle(char* msj);
		void changeRegresiveTime(char* msj);
		void loadPower(int player_id, Gusano* gusano, int& turn_actual_len);
		void fire(int player_id, Gusano* gusano, int& turn_actual_len);
		void fire_bazooka(Gusano* gusano, b2Vec2 position);
		void fire_morter(Gusano* gusano, b2Vec2 position);
		
		
	public:
		Turn(b2World& world_e, ProtectedQueue& queue_e, std::map<int, std::map<int, Gusano*>>& players_e, 
			std::vector<std::pair<int, int>>& to_remove_gusanos_e, GameConstants& info_e, MultipleProxy& proxy_e);
		
		~Turn();
		
		void play(int player_id, unsigned int gusano_id);
};

#endif
