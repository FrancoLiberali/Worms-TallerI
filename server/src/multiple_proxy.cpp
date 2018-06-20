#include "multiple_proxy.h"
#include <cmath>
#include <iostream>
#include <utility>

MultipleProxy::MultipleProxy(){
}

MultipleProxy::~MultipleProxy(){
}

void MultipleProxy::add(int id, Proxy* proxy){
	this->proxys.insert(std::pair<int, Proxy*>(id, proxy));
}

Proxy* MultipleProxy::erase(int id){
	std::cout << "tam: " << this->proxys.size() << "\n";
	Proxy* erased = this->proxys[id];
	this->proxys.erase(id);
	return erased;
}

void MultipleProxy::addNewQueue(ProtectedQueue* queue){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->addNewQueue(queue);
	}
}

void MultipleProxy::changeToPrevQueue(){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->changeToPrevQueue();
	}
}

void MultipleProxy::sendPlayerName(int player_id, std::string& name){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendPlayerName(player_id, name);
	}
}

void MultipleProxy::sendVigaCreation(int x, int y, int angle){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendVigaCreation(x, y, angle);
	}
}

void MultipleProxy::sendMapDimentions(int widht, int height){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendMapDimentions(widht * 1000, height * 1000);
	}
}

void MultipleProxy::sendGusanoCreation(int gusano_id, int player_id, float x, float y, int direction, float angle){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendGusanoCreation(gusano_id, player_id, (int)(x * 1000), (int)(y * 1000), direction, (int) (angle * 180 / M_PI));
	}
}

void MultipleProxy::sendTurnBegining(int player_id, int gusano_id){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendTurnBegining(player_id, gusano_id);
	}
}

void MultipleProxy::sendGusanoPosition(int gusano_id, float x, float y, int direction, float angle){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendGusanoPosition(gusano_id, (int)(x * 1000), (int)(y * 1000), direction, (int) (angle * 180 / M_PI));
	}
}

void MultipleProxy::sendStateChange(int gusano_id, int new_state){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendStateChange(gusano_id, new_state);
	}
}

void MultipleProxy::sendProjectilePosition(int projectile_number, int weapon, float x, float y, float angle){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendProjectilePosition(projectile_number, weapon, (int)(x * 1000), (int)(y * 1000), (int) (angle * 180 / M_PI));
	}
}

void MultipleProxy::sendProjectileExplosion(int projectile_number, float x, float y){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendProjectileExplosion(projectile_number, (int)(x * 1000), (int)(y * 1000));
	}
}

void MultipleProxy::sendTakeWeapon(int weapon){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendTakeWeapon(weapon);
	}
}

void MultipleProxy::sendChangeSightAngle(int change){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendChangeSightAngle(change);
	}
}

void MultipleProxy::sendLifeChange(int gusano_id, int new_life){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendLifeChange(gusano_id, new_life);
	}
}

void MultipleProxy::sendPlayerDisconnection(int player_id){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		std::cout << "hay proxy\n";
		std::cout << "id: " << it->first << "\n";
		it->second->sendPlayerDisconnection(player_id);
	}
}

void MultipleProxy::sendPlayerLoose(int player_id){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendPlayerLoose(player_id);
	}
}

void MultipleProxy::sendGameWon(int player_id){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendGameWon(player_id);
	}
}

void MultipleProxy::sendRoomCreation(int room_id, const std::string& name, 
	int cant_players, int max_players, const std::string& map_name){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendRoomCreation(room_id, name, cant_players, max_players, map_name);
	}
}

void MultipleProxy::sendRoomPlayersChange(int room_id, int cant_players){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendRoomPlayersChange(room_id, cant_players);
	}
}

void MultipleProxy::sendRoomDeletion(int room_id){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendRoomDeletion(room_id);
	}
}

void MultipleProxy::sendPlayerConnection(int id, const std::string& name){
	std::map<int, Proxy*>::iterator it = this->proxys.begin();
	for (; it != this->proxys.end(); ++it){
		it->second->sendPlayerConnection(id, name);
	}
}
		
