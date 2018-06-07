#include "multiple_proxy.h"

MultipleProxy::MultipleProxy(){
}

MultipleProxy::~MultipleProxy(){
}

void MultipleProxy::add(Proxy* proxy){
	this->proxys.push_back(proxy);
}

void MultipleProxy::sendTurnBegining(int player_id, int gusano_id){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendTurnBegining(player_id, gusano_id);
	}
}

void MultipleProxy::send_state_change(int player_id, int gusano_id, int new_state){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->send_state_change(player_id, gusano_id, new_state);
	}
}
		
void MultipleProxy::send_gusano_position(int player_id, int gusano_id, int x, int y, int direction, int angle){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->send_gusano_position(player_id, gusano_id, x, y, direction, angle);
	}
}

void MultipleProxy::send_viga_position(int x, int y, int angle){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->send_viga_position(x, y, angle);
	}
}

void MultipleProxy::send_projectile_creation(int projectile_number, int weapon, int x, int y, int angle){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->send_projectile_creation(projectile_number, weapon, x, y, angle);
	}
}

void MultipleProxy::sendProjecileExplosion(int projectile_number, float x, float y){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendProjectileExplosion(projectile_number, (int)x * 1000, (int) y * 1000);
	}
}

void MultipleProxy::sendTakeWeapon(int weapon){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendTakeWeapon(weapon);
	}
}

void MultipleProxy::sendChangeSightAngle(int change){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendChangeSightAngle(change);
	}
}
		
