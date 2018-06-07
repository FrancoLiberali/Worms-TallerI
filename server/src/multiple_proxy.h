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
		
		void send_gusano_position(int player_id, int gusano_id, int x, int y, int direction, int angle);
		
		void send_viga_position(int x, int y, int angle);
		
		void send_projectile_creation(int projectile_number, int weapon, int x, int y, int angle);
		
		void sendProjecileExplosion(int projectile_number, float x, float y);
		
		void sendTakeWeapon(int weapon);
		
		void sendChangeSightAngle(int change);
		
		//void delete(int id);
		
};

#endif
