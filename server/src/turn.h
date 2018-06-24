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
		
		//interpretacion de todos los mensajes enviados por todos los jugadores hasta el momento
		// y aplicacion de los cambios correspondientes a estos mensajes, si los mismos son validos
		void interpretMessages(int active_player,Gusano& gusano_actual, bool& continue_turn, int& turn_actual_len);
		
		
		// procesa la lista to_remove_projectiles,
		// en la cual se agregaron durante la simulacion
		// los ids de los projectiles que deben ser eliminados del modelo
		// dada su explosion
		void processProjectilesDeletion();
		
		// procesa el map to_remove_gusanos,
		// en el cual se agregaron durante la simulacion
		// los ids de los gusanos que deben ser eliminados del modelo
		// dada su eliminacion: muerieron a volaron mas alla de los limites de mapa
		void processGusanosDeletion(int active_gusano, int& turn_actual_len);
		
		// proce la lista to_create
		// en la cual se agregaron durante la simulacion
		// los objetos FragmentInfo que contienen la informacion
		// para crear los pequenios proyectiles causado por 
		// la explosion de un proyectil fragmentario
		void processProjectilesCreation();
		
		// determina si debe haber algun cambio en el viento
		// el viento cambia cada un determinado tiempo
		// siempre y cuando no hay ningun proyectil ya en vuelo 
		void processWindChange(int turn_actual_len);
		
		// actualiza los proyectiles en vuelo
		void processProjectilesInFlight(bool& something_to_simulate);
		
		// actualiza los gusanos vivos y manda la informacion de los que
		// se encuentren realizando alguna accion
		void processAliveGusanos(bool& something_to_simulate);
	
		
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
		
		// Hace que se juege un turno, realizado la simulacion de los mensajes
		// que los juadores envien y manejando cuando debe terminar un turno.
		void play(int player_id, unsigned int gusano_id);
};

#endif
