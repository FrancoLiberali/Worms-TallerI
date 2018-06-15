#include "socket.h"
#include "protected_queue.h"
#include <string>
#include <vector>
#include <map>

#ifndef __PROXY_H__
#define __PROXY_H__

class Proxy{
	private:
		Socket socket;
		int id = 0;
		ProtectedQueue* queue;
		ProtectedQueue* prev_queue;
		
		void receive_event_info(char event, int tam);
		void receiveNameToQueue(char event, int cant_ints);
	public:
		// Objeto que envia todos los mensajes a un juagador via 
		// el socket recibido.
		// La estructura de los mensajes respeta el protocolo
		// de comunicacion definido para este programa
		Proxy(Socket socket_e, ProtectedQueue* queue);
		
		~Proxy() noexcept;
		
		void close_communication();
		
		void addNewQueue(ProtectedQueue* queue);
		
		void changeToPrevQueue();
		
		std::string receiveName();
		
		void receive_event();
		
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
		
		void sendPlayerLoose(int player_id);
		
		void sendGameWon(int player_id);
		
		void sendRoomCreation(const std::string& name, int cant_players, int max_players, unsigned int map_id);
		
		void sendRoomPlayersChange(const std::string& name, int cant_players);
		
		void sendRoomDeletion(const std::string& name);
		
		void sendPlayerConnection(int id, const std::string& name);
		
		void sendRoomNameError();
		
		void send_int(int to_send);
		
};

#endif
