#include "server/multiple_proxy.h"
#include <cmath>
#include <iostream>
#include <utility>

#define TO_MILIMETERS 1000
#define TO_KM_PER_HOUR 100
#define TO_GRADES 180.0 / M_PI

MultipleProxy::MultipleProxy(){
}

MultipleProxy::~MultipleProxy(){
}

void MultipleProxy::add(int id, Proxy& proxy){
	this->proxys.insert(std::pair<int, Proxy&>(id, proxy));
}

Proxy& MultipleProxy::erase(int id){
	Proxy& erased = this->proxys.at(id);
	this->proxys.erase(id);
	return erased;
}

void MultipleProxy::addNewQueue(ProtectedQueue* queue){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.addNewQueue(queue);
	}
}

void MultipleProxy::changeToPrevQueue(){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.changeToPrevQueue();
	}
}

void MultipleProxy::sendMapBackground(std::string& background){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendMapBackground(background);
	}
}

void MultipleProxy::sendVigaCreation(float x, float y, float angle){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendVigaCreation((int)(x * TO_MILIMETERS), (int)(y * TO_MILIMETERS), (int) (angle * TO_GRADES));
	}
}

void MultipleProxy::sendMapDimentions(int widht, int height){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendMapDimentions(widht * TO_MILIMETERS, height * TO_MILIMETERS);
	}
}

void MultipleProxy::sendGusanoCreation(int gusano_id, int player_id, float x, float y, int direction, float angle){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendGusanoCreation(gusano_id, player_id, (int)(x * TO_MILIMETERS), (int)(y * TO_MILIMETERS),
									  direction, (int) (angle * TO_GRADES));
	}
}

void MultipleProxy::sendTurnBegining(int player_id, int gusano_id){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendTurnBegining(player_id, gusano_id);
	}
}

void MultipleProxy::sendGusanoPosition(int gusano_id, float x, float y, int direction, float angle){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendGusanoPosition(gusano_id, (int)(x * TO_MILIMETERS), (int)(y * TO_MILIMETERS), 
									  direction, (int) (angle * TO_GRADES));
	}
}

void MultipleProxy::sendStateChange(int gusano_id, int new_state){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendStateChange(gusano_id, new_state);
	}
}

void MultipleProxy::sendProjectileCreation(int projectile_number, int weapon, int direction, float x, float y, float angle){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendProjectileCreation(projectile_number, weapon, direction, (int)(x * TO_MILIMETERS), 
											(int)(y * TO_MILIMETERS), (int) (angle * TO_GRADES));
	}
}

void MultipleProxy::sendProjectilePosition(int projectile_number, float x, float y, float angle){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendProjectilePosition(projectile_number, (int)(x * TO_MILIMETERS), (int)(y * TO_MILIMETERS), 
										 (int) (angle * TO_GRADES));
	}
}

void MultipleProxy::sendProjectileExplosion(int projectile_number){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendProjectileExplosion(projectile_number);
	}
}

void MultipleProxy::sendTakeWeapon(int weapon){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendTakeWeapon(weapon);
	}
}

void MultipleProxy::sendChangeSightAngle(int change){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendChangeSightAngle(change);
	}
}

void MultipleProxy::sendLifeChange(int gusano_id, int new_life){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendLifeChange(gusano_id, new_life);
	}
}

void MultipleProxy::sendPlayerDisconnection(int player_id){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendPlayerDisconnection(player_id);
	}
}

void MultipleProxy::sendPlayerLoose(int player_id){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendPlayerLoose(player_id);
	}
}

void MultipleProxy::sendGameWon(int player_id){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendGameWon(player_id);
	}
}

void MultipleProxy::sendRoomCreation(int room_id, const std::string& name, 
	int cant_players, int max_players, const std::string& map_name){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendRoomCreation(room_id, name, cant_players, max_players, map_name);
	}
}

void MultipleProxy::sendRoomPlayersChange(int room_id, int cant_players){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendRoomPlayersChange(room_id, cant_players);
	}
}

void MultipleProxy::sendRoomDeletion(int room_id){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendRoomDeletion(room_id);
	}
}

void MultipleProxy::sendPlayerConnection(int id, const std::string& name){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendPlayerConnection(id, name);
	}
}

void MultipleProxy::sendFinishedAmunnition(int player_id, int weapon_id){
	this->proxys.at(player_id).sendFinishedAmunnition(weapon_id);
}

void MultipleProxy::sendRemoteWork(int weapon_id){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendRemoteWork(weapon_id);
	}
}

void MultipleProxy::sendSecond(){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendSecond();
	}
}

void MultipleProxy::sendWindChange(float wind){
	std::map<int, Proxy&>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second.sendWindChange((int)(wind * TO_KM_PER_HOUR));
	}
}
		
