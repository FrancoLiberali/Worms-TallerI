#include <vector>
#include "proxy.h"

#ifndef __MULTIPLE_PROXY_H__
#define __MULTIPLE_PROXY_H__

class MultipleProxy{
	private:
		std::vector<Proxy*> proxys;
		
	public:
		MultipleProxy();
		
		~MultipleProxy();
		
		void add(Proxy* proxy);
		
		void sendTurnBegining(int player_id, int gusano_id);
		
		void send_state_change(int player_id, int gusano_id, int new_state);
		
		void sendGusanoPosition(int player_id, int gusano_id, float x, float y, int direction, float angle);
		
		void send_viga_position(int x, int y, int angle);
		
		void sendProjectilePosition(int projectile_number, int weapon, float x, float y, float angle);
		
		void sendProjecileExplosion(int projectile_number, float x, float y);
		
		void sendTakeWeapon(int weapon);
		
		void sendChangeSightAngle(int change);
		
		void sendLifeChange(int player_id, int gusano_id, int new_life);
		
		//void delete(int id);
		
};

#endif
