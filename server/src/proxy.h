#include "socket.h"
#include "protected_queue.h"

#ifndef __PROXY_H__
#define __PROXY_H__

class Proxy{
	private:
		Socket socket;
		
		void receive_event_info(ProtectedQueue& queue, char event, int tam);
	public:
		Proxy(Socket socket_e);
		
		~Proxy() noexcept;
		
		void close_communication();
		
		/*void send_viga(Socket& socket, const Viga& viga);
		
		void send_gusano(Socket& socket, const Gusano& gusano, unsigned int number);
		
		void send_position(Socket& socket, const b2Vec2& pos);
		
		void send_movement(Socket& socket, unsigned int gusano_number, int direction);
		
		void send_unsigned_int(Socket& socket, unsigned int num);
		
		void send_int(Socket& socket, int num);
		
		void send_float(Socket& socket, float num);
		
		void send_char(Socket& socket, const char to_send);*/
		
		void receive_event(ProtectedQueue& queue);
		
		const unsigned char receive_char();
		
		void sendPlayerId(int id);
		
		void sendTurnBegining(int player_id, int gusano_id);
		
		void send_viga_position(int x, int y, int angle);
		
		void send_gusano_position(int player_id, int gusano_id, int x, int y, int direction, int angle);
		
		void send_state_change(int player_id, int gusano_id, int new_state);
		
		void send_projectile_creation(int projectile_number, int weapon, int x, int y, int angle);
		
		void sendProjectileExplosion(int projectile_number, int x, int y);
		
		void sendTakeWeapon(int weapon);
		
		void sendChangeSightAngle(int change);
		
		void send_int(int to_send);
		
		/*const float receive_float(Socket& socket);
		
		const unsigned int receive_unsigned_int(Socket& socket);
		
		const int receive_int(Socket& socket);*/
		
};

#endif
