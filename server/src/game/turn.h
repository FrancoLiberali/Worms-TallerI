#include "Box2D/Box2D.h"
#include <map>
#include "server/proxy.h"
#include "game/weapons/projectile.h"
#include "game/game_constants.h"
#include "game/gusano/gusano.h"
#include "server/multiple_proxy.h"
#include "game/weapons/fragment_info.h"
#include <utility>
#include "game/objects_factory.h"

#ifndef __TURN_H__
#define __TURN_H__

class Turn{
	private:
		b2World& world;
		ProtectedQueue& queue;
		std::map<int, std::map<int, Gusano>>& players;
		std::vector<std::pair<int, int>>& to_remove_gusanos;
		const GameConstants& info;
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
	
		// Desconecta al jugador player_id de la partida.
		// Avisa a todo el resto de jugadores de su desconeccion
		// elimina sus gusanos y termina el turno si el turno
		// actual era de el.
		void disconnect(int player_id, int active_player, int& turn_actual_len);
		
		// interpreta del msj la direccion en la que
		// debe ser el movimiento y mueve al gusano.
		void gusanoMove(char* msj, Gusano& gusano);
		
		// Interpreta del mensaje el arma a sacar,
		// saca el arma si el jugador player_id aun tiene municion
		// de esa arma y setea todas las variables del 
		// arma(poder, angulo de mira, etc) al default.
		void takeWeapon(int player_id, char* msj);
		
		// Interpreta del msj la direccion del cambio
		// y aumenta o reduce el angulo de la mira del arma
		// si el arma lo permite.
		void changeSightAngle(char* msj);
		
		// Interpreta del mensaje el tiempo que se desea que sea el 
		// tiempo de explosion del arma actual y lo setea
		void changeRegresiveTime(char* msj);
		
		// Carga poder al arma si el arma lo permite.
		// Si se llega al poder maximo se dispara automaticamente.
		void loadPower(int player_id, Gusano& gusano, int& turn_actual_len);
		
		// Dispara el arma que tenga el gusano actual.
		// Llama a la factory para crear el proyectil.
		void fire(int player_id, Gusano& gusano, int& turn_actual_len);
		
		// Setea las variables del turno a que ya se disparo un arma.
		void setFired(int player_id, int& turn_actual_len);
		
		// Interpreta del mensaje la posicion a la que se quiere
		// cambiar el objetivo de un arma teledirigida y la setea.
		void changeRemoteObjetive(char* msj);
		
		// Chequea que el objetivo de arma teledirigida sea valido
		// y dispara el ataque aereo.
		void fireAirAttack(int player_id, int& turn_actual_len);
		
		// Chequea que el objetivo de arma teledirigida este desocupado
		// y teletransporta al gusano.
		void teleport(int player_id, int& turn_actual_len, Gusano& gusano);
		
	public:
		// Crea el objeto turn, se setean todas las variables necesarias para empezar los turnos de
		// los jugadores y se agrega a la factory la informacion del turno.
		Turn(b2World& world_e, ProtectedQueue& queue_e, std::map<int, std::map<int, Gusano>>& players_e, 
			std::vector<std::pair<int, int>>& to_remove_gusanos_e,
			const GameConstants& info_e, MultipleProxy& proxy_e,
			ObjectsFactory& factory);
		
		~Turn();
		
		// Hace que se juege un turno, realizado la simulacion de los mensajes
		// que los juadores envien y manejando cuando debe terminar un turno.
		void play(int player_id, unsigned int gusano_id);
};

#endif
