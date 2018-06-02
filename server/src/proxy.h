#include "socket.h"
#include "gusano.h"
#include "viga.h"
#include "turn.h"

#ifndef __PROXY_H__
#define __PROXY_H__

class Proxy{
	public:
		Proxy();
		
		~Proxy() noexcept;
		
		void send_viga(Socket& socket, const Viga& viga);
		
		void send_gusano(Socket& socket, const Gusano& gusano, unsigned int number);
		
		void send_position(Socket& socket, const b2Vec2& pos);
		
		void send_movement(Socket& socket, unsigned int gusano_number, int direction);
		
		void send_unsigned_int(Socket& socket, unsigned int num);
		
		void send_int(Socket& socket, int num);
		
		void send_float(Socket& socket, float num);
		
		void send_char(Socket& socket, const char to_send);
		
		void receive_event(Socket& socket, Turn& turn);
		
		const unsigned char receive_char(Socket& socket);
		
		const float receive_float(Socket& socket);
		
		const unsigned int receive_unsigned_int(Socket& socket);
		
		const int receive_int(Socket& socket);
		
};

#endif
