#include "multiple_proxy.h"
#include <cmath>
#include <iostream>

MultipleProxy::MultipleProxy(){
}

MultipleProxy::~MultipleProxy(){
}

void MultipleProxy::add(Proxy* proxy){
	this->proxys.push_back(proxy);
}

void MultipleProxy::erase(int id){
	this->proxys.erase(this->proxys.begin() + (id - 1));
	std::cout << this->proxys.size() << "\n";
}

void MultipleProxy::sendPlayerName(int player_id, std::string& name){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendPlayerName(player_id, name);
	}
}

void MultipleProxy::sendVigaCreation(int x, int y, int angle){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendVigaCreation(x, y, angle);
	}
}

void MultipleProxy::sendGusanoCreation(int gusano_id, int player_id, float x, float y, int direction, float angle){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendGusanoCreation(gusano_id, player_id, (int)(x * 1000), (int)(y * 1000), direction, (int) (angle * 180 / M_PI));
	}
}

void MultipleProxy::sendTurnBegining(int player_id, int gusano_id){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendTurnBegining(player_id, gusano_id);
	}
}

void MultipleProxy::sendGusanoPosition(int gusano_id, float x, float y, int direction, float angle){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendGusanoPosition(gusano_id, (int)(x * 1000), (int)(y * 1000), direction, (int) (angle * 180 / M_PI));
	}
}

void MultipleProxy::sendStateChange(int gusano_id, int new_state){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendStateChange(gusano_id, new_state);
	}
}

void MultipleProxy::sendProjectileCreation(int projectile_number, int weapon, int direction, float x, float y, float angle){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendProjectileCreation(projectile_number, weapon, direction, (int)(x * 1000), (int)(y * 1000), (int) (angle * 180 / M_PI));
	}
}

void MultipleProxy::sendProjectilePosition(int projectile_number, float x, float y, float angle){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendProjectilePosition(projectile_number, (int)(x * 1000), (int)(y * 1000), (int) (angle * 180 / M_PI));
	}
}

void MultipleProxy::sendProjectileExplosion(int projectile_number){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendProjectileExplosion(projectile_number);
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

void MultipleProxy::sendLifeChange(int gusano_id, int new_life){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendLifeChange(gusano_id, new_life);
	}
}

void MultipleProxy::sendPlayerDisconnection(int player_id){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendPlayerDisconnection(player_id);
	}
}

void MultipleProxy::sendGameWon(int player_id){
	std::vector<Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		(*it)->sendGameWon(player_id);
	}
}
		
