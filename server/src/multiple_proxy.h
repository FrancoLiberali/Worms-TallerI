#include <vector>
#include "proxy.h"
#include <string>
#include "protected_queue.h"
#include <mutex>
#include <map>


#ifndef __MULTIPLE_PROXY_H__
#define __MULTIPLE_PROXY_H__

class MultipleProxy{
	private:
		std::map<int, Proxy*> proxys;
		std::mutex mutex;
		
	public:
		// Crea el objeto, el cual tiene la finalidad de contener
		// distintos proxys que se van a comunicar con distintos juagores
		// para enviarle a todos los jugadores el mismo mensaje.
		MultipleProxy();
		
		~MultipleProxy();
		
		// Agrega un proxy a la lista de proxys a la cual se le enviaran 
		// todos los mensajes
		void add(int id, Proxy* proxy);
		
		// Saca un jugador de la lista de proxys segun su id, para que
		// deje de recibir los mensajes del juego
		Proxy* erase(int id);
		
		void addNewQueue(ProtectedQueue* queue);
		
		void changeToPrevQueue();
		
		void sendPlayerName(int player_id, std::string& name);
		
		void sendVigaCreation(int x, int y, int angle);
		
		void sendGusanoCreation(int gusano_id, int player_id, float x, float y, int direction, float angle);
		
		void sendTurnBegining(int player_id, int gusano_id);
		
		void sendGusanoPosition(int gusano_id, float x, float y, int direction, float angle);
		
		void sendStateChange(int gusano_id, int new_state);
				
		void sendProjectilePosition(int projectile_number, int weapon, float x, float y, float angle);
		
		void sendProjectileExplosion(int projectile_number, float x, float y);
		
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
		
};

#endif
