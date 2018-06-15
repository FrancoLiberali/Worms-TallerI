#include <vector>
#include "proxy.h"
#include <string>

#ifndef __MULTIPLE_PROXY_H__
#define __MULTIPLE_PROXY_H__

class MultipleProxy{
	private:
		std::vector<Proxy*> proxys;
		
	public:
		// Crea el objeto, el cual tiene la finalidad de contener
		// distintos proxys que se van a comunicar con distintos juagores
		// para enviarle a todos los jugadores el mismo mensaje.
		MultipleProxy();
		
		~MultipleProxy();
		
		// Agrega un proxy a la lista de proxys a la cual se le enviaran 
		// todos los mensajes
		void add(Proxy* proxy);
		
		// Saca un jugador de la lista de proxys segun su id, para que
		// deje de recibir los mensajes del juego
		void erase(int id);
		
		void sendPlayerName(int player_id, std::string& name);
		
		void sendVigaCreation(int x, int y, int angle);
		
		void sendGusanoCreation(int gusano_id, int player_id, float x, float y, int direction, float angle);
		
		void sendTurnBegining(int player_id, int gusano_id);
		
		void sendGusanoPosition(int gusano_id, float x, float y, int direction, float angle);
		
		void sendStateChange(int gusano_id, int new_state);
		
		void sendProjectileCreation(int projectile_number, int weapon, int direction, float x, float y, float angle);
				
		void sendProjectilePosition(int projectile_number, float x, float y, float angle);
		
		void sendProjectileExplosion(int projectile_number);
		
		void sendTakeWeapon(int weapon);
		
		void sendChangeSightAngle(int change);
		
		void sendLifeChange(int gusano_id, int new_life);
		
		void sendPlayerDisconnection(int player_id);
		
		void sendGameWon(int player_id);
		
};

#endif
