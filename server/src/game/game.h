#include "Box2D/Box2D.h"
#include "util/thread.h"
#include <map>
#include "server/socket.h"
#include "util/protected_queue.h"
#include "game/game_constants.h"
#include "game/gusano/gusano.h"
#include "game/Box2d_elements/contact_listener.h"
#include <mutex>
#include "server/multiple_proxy.h"
#include "game/delimiter.h"
#include "game/objects_factory.h"

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
		std::vector<std::pair<int, int>> to_remove_gusanos;
		ObjectsFactory factory;
		std::map<int, std::map<int, Gusano>> players;
		std::vector<int> next;
		int gusanos_per_player;
		GameConstants info;
		
	public:
		// Crea el objeto game, creando el mundo de simulaciones fisicas
		// y agregando en el todos los objetos del juego.
		// La informacion de estos objetos deberia es leida del archivo yalm
		// especificado por el map_name.
		// Ademas se asignan a cada jugador sus correspondientes gusanos.
		Game(MultipleProxy& proxy_e, ProtectedQueue& queue_e, const std::string& map_name, std::vector<int> players_ids);
		
		~Game();
		
		// Inicia una partida, controlando el sistema de turnos.
		void play();
};

#endif
