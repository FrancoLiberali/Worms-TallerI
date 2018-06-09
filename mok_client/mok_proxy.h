#include "socket.h"

#ifndef __MOK_PROXY_H__
#define __MOK_PROXY_H__

class MokProxy{
	private:
		Socket& socket;
		int id = 0;
		
		void send_int(int to_send);
		int receive_int();
		void sendMapAndPlayers(int map, int players);
	public:
		MokProxy(Socket& socket);
		
		~MokProxy();
		
		void close_communication();
		
		void receive_event();
		
		void send(char event);
		
};

#endif
