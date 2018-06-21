#include "Box2D/Box2D.h"
#include "thread.h"
#include <map>
#include "socket.h"
#include "protected_queue.h"
#include "game_constants.h"
#include "gusano.h"
#include "water.h"
#include "contact_listener.h"
#include <mutex>
#include "multiple_proxy.h"
#include "delimiter.h"

#ifndef __GAME_H__
#define __GAME_H__

class Game {
	private:
		MultipleProxy& proxy;
		ProtectedQueue& queue;
		b2World world;
		std::vector<int> players_ids;
		ContactListener contact_listener;
		std::vector<Delimiter> delimiters;
		//Water* water;
		std::vector<std::pair<int, int>> to_remove_gusanos;
		std::map<int, std::map<int, Gusano>> players;
		std::vector<int> next;
		int gusanos_per_player;
		GameConstants info;
		
	public:
		// Crea el objeto game, creando el mundo de simulaciones fisicas
		// y agregando en el todos los objetos del juego.
		// La informacion de estos objetos deberia ser leida del archivo yalm
		// especificado por el map_id, lo que aun no esta implementado y
		// la creacion del mapa se hace aqui mismo.
		// Ademas se asignan a cada jugador sus correspondientes gusanos.
		Game(MultipleProxy& proxy_e, ProtectedQueue& queue_e, std::string& map_name, std::vector<int> players_ids);
		
		~Game();
		
		// Inicia una partida, controlando el sistema de turnos.
		void play();
};

#endif
