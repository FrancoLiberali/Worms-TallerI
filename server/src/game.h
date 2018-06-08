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

#ifndef __GAME_H__
#define __GAME_H__

class Game {
	private:
		MultipleProxy& proxy;
		ProtectedQueue& queue;
		b2World world;
		int cant_players;
		ContactListener contact_listener;
		Water* water;
		std::vector<std::pair<int, int>> to_remove_gusanos;
		std::map<int, std::map<int, Gusano*>> players;
		std::vector<int> next;
		int gusanos_per_player;
		GameConstants info;
		
	public:
		Game(MultipleProxy& proxy_e, ProtectedQueue& queue_e, unsigned int map_id, int cant_players);
		
		~Game();
		
		void play();
};

#endif
