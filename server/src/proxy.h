#include "socket.h"
#include "protected_queue.h"
#include <string>

#ifndef __PROXY_H__
#define __PROXY_H__

class Proxy{
	private:
		Socket socket;
		int id = 0;
		
		void receive_event_info(ProtectedQueue& queue, char event, int tam);
	public:
		// Objeto que envia todos los mensajes a un juagador via 
		// el socket recibido.
		// La estructura de los mensajes respeta el protocolo
		// de comunicacion definido para este programa
		Proxy(Socket socket_e);
		
		~Proxy() noexcept;
		
		void close_communication();
		
		void receive_event(ProtectedQueue& queue);
		
		const unsigned char receive_char();
		
		void sendPlayerId(int id);
		
		void sendPlayerName(int player_id, std::string& name);
		
		void sendVigaCreation(int x, int y, int angle);
		
		void sendGusanoCreation(int gusano_id, int player_id, int x, int y, int direction, int angle);
		
		void sendTurnBegining(int player_id, int gusano_id);
		
		void sendGusanoPosition(int gusano_id, int x, int y, int direction, int angle);
		
		void sendStateChange(int gusano_id, int new_state);
				
		void sendProjectilePosition(int projectile_number, int weapon, int x, int y, int angle);
		
		void sendProjectileExplosion(int projectile_number, int x, int y);
		
		void sendTakeWeapon(int weapon);
		
		void sendChangeSightAngle(int change);
		
		void sendLifeChange(int gusano_id, int new_life);
		
		void sendPlayerDisconnection(int player_id);
		
		void sendGameWon(int player_id);
		
		void send_int(int to_send);
		
};

#endif
