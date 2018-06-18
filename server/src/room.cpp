#include "room.h"
#include "game.h"

Room::Room(std::string name_e, unsigned int map_id_e, int max_players_e) : 
		name(std::move(name_e)), map_id(map_id_e), max_players(max_players_e){
	
}

Room::~Room(){
}

std::string& Room::getName(){
	return this->name;
}

void Room::add(int player_id, std::string& player_name, Proxy* player_proxy){
	std::map<int, std::string&>::iterator names_it = names.begin();
	for (; names_it != names.end(); ++names_it){
		player_proxy->sendPlayerConnection(names_it->first, names_it->second);
	}
	this->names.insert(std::pair<int, std::string&>(player_id, player_name));
	this->proxy.sendPlayerConnection(player_id, player_name);
	this->proxy.add(player_id, player_proxy);
}

void Room::erase(int player_id){
	this->names.erase(player_id);
	this->proxy.erase(player_id);
	this->proxy.sendPlayerDisconnection(player_id);
	//se va a mandar dos veces porque se manda desde aca tambien
}

void Room::run(){
	this->proxy.addNewQueue(&(this->queue));
	this->active = true;
	std::vector<int> players;
	std::map<int, std::string&>::iterator it = names.begin();
	for(; it != names.end(); ++it){
		players.push_back(it->first);
	}
	//Game game(this->proxy, this->queue, this->map_id, players);
	//cuando termina vuelven a mandar mensajes a la hall
	this->proxy.changeToPrevQueue(); 
}

void Room::stop(){
}

bool Room::isActive(){
	return this->active;
}

int Room::cantPlayers(){
	return (this->names.size());
}

int Room::maxPlayers(){
	return this->max_players;
}

unsigned int Room::mapId(){
	return this->map_id;
}
