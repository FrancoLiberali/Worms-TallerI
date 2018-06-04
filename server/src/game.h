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
#include "proxy.h"
#include "fake_proxy/mok_proxy.h"

#ifndef __GAME_H__
#define __GAME_H__

class Game {
	private:
		//Proxy proxy;
		ProtectedQueue& queue;
		b2World world;
		MokProxy proxy;
		ContactListener contact_listener;
		Water* water;
		std::map<unsigned int, Gusano*> gusanos;
		std::map<unsigned int, Gusano*> to_remove_gusanos;
		GameConstants info;
		
	public:
		Game(Socket& socket_e, ProtectedQueue& queue_e);
		
		~Game();
		
		void play();
};

#endif
