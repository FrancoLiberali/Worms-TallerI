#include "Box2D/Box2D.h"
#include <map>
#include "proxy.h"
#include "projectile.h"
#include "game_constants.h"
#include "gusano.h"
#include "multiple_proxy.h"
#include "fragment_info.h"
#include <utility>
#include "objects_factory.h"

#ifndef __TURN_H__
#define __TURN_H__

class Turn{
	private:
		b2World& world;
		ProtectedQueue& queue;
		std::map<int, std::map<int, Gusano>>& players;
		std::vector<std::pair<int, int>>& to_remove_gusanos;
		GameConstants& info;
		MultipleProxy& proxy;
		ObjectsFactory& factory;
		std::map<int, std::vector<int>> ammunition;
		std::map<int, std::unique_ptr<Projectile>> projectiles;
		std::vector<int> to_remove_projectiles;
		int actual_max_projectile = 0;
		std::vector<FragmentInfo> to_create;
		int weapon = 0;
		float sight_angle = 0;
		unsigned int regresive_time = 5;
		float power = 1;
		bool fired;
		b2Vec2 remote_position;
		float wind = 0;
		
		void disconnect(int player_id, int active_player, int& turn_actual_len);
		void gusano_move(char* msj, Gusano& gusano);
		void gusano_jump(Gusano& gusano);
		void gusano_back_jump(Gusano& gusano);
		void take_weapon(int player_id, char* msj);
		void changeSightAngle(char* msj);
		void changeRegresiveTime(char* msj);
		void loadPower(int player_id, Gusano& gusano, int& turn_actual_len);
		void fire(int player_id, Gusano& gusano, int& turn_actual_len);
		void setFired(int player_id, int& turn_actual_len);
		void changeRemoteObjetive(char* msj);
		void fire_air_attack(int player_id, int& turn_actual_len);
		void teleport(int player_id, int& turn_actual_len, Gusano& gusano);
		
	public:
		Turn(b2World& world_e, ProtectedQueue& queue_e, std::map<int, std::map<int, Gusano>>& players_e, 
			std::vector<std::pair<int, int>>& to_remove_gusanos_e,
			GameConstants& info_e, MultipleProxy& proxy_e,
			ObjectsFactory& factory);
		
		~Turn();
		
		void play(int player_id, unsigned int gusano_id);
};

#endif
