#include "socket.h"
#include <string>
#include <vector>

#ifndef __MOK_PROXY_H__
#define __MOK_PROXY_H__

class MokProxy{
	private:
		Socket& socket;
		std::string room_name;
		std::string* map_name = nullptr;
		int id = 0;
		int last_room_id = 0;
		
		void send_int(int to_send);
		int receive_int();
		void sendMapAndPlayers(int map, int players);
	public:
		MokProxy(Socket& socket);
		
		~MokProxy();
		
		void close_communication();
		
		void sendName(std::string name);
		
		void receive_event();
		
		void send(char event);
		
};

#endif
