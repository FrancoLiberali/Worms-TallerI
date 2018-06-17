#include "thread.h"
#include "multiple_proxy.h"
#include "proxy.h"
#include <vector>
#include <string>

#ifndef __ROOM_H__
#define __ROOM_H__

class Room : public Thread{
	private:
		std::string name;
		unsigned int map_id;
		int max_players;
		std::map<int, std::string> names;
		MultipleProxy proxy;
		ProtectedQueue queue;
		bool active = false;
		
	public:
		Room(std::string name, unsigned int map_id_e, int max_players_e);
		
		~Room();
		
		std::string getName();
		
		void add(int player_id, std::string player_name, Proxy* player_proxy);
		
		void erase(int player_id);
		
		virtual void run();
		
		virtual void stop();
		
		bool isActive();
		
		int cantPlayers();
		
		int maxPlayers();
		
		unsigned int mapId();
};

#endif
	
