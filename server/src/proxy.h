#include "socket.h"
#include "queue.h"
#include <string>
#include <vector>
#include <map>
#include <mutex>

#ifndef __PROXY_H__
#define __PROXY_H__

class Proxy{
	private:
		Socket socket;
		int id = 0;
		Queue* queue;
		Queue* prev_queue;
		std::mutex queue_mutex;
		
		void receive_event_info(char event, int tam);
		void pushDisconnectionMessage();
	public:
		// Objeto que envia todos los mensajes a un juagador via 
		// el socket recibido.
		// La estructura de los mensajes respeta el protocolo
		// de comunicacion definido para este programa
		Proxy(Socket socket_e, Queue* queue);
		
		~Proxy() noexcept;
		
		void close_communication();
		
		void addNewQueue(Queue* queue);
		
		void changeToPrevQueue();
		
		std::string receiveName();
		
		void receive_event();
		
		void disconnect();
		
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
		
		void sendRoomCreation(int room_id, const std::string& name, int cant_players, int max_players, const std::string& map_name);
		
		void sendRoomPlayersChange(int room_id, int cant_players);
		
		void sendRoomDeletion(int room_id);
		
		void sendPlayerConnection(int id, const std::string& name);
		
		void sendAvailableMaps(std::vector<std::string>& maps);
		
		void send_int(int to_send);
		
};

#endif
