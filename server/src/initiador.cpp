#include "initiador.h"
#include <arpa/inet.h>
#include <iostream>
#include "blocking_queue.h"

Initiador::Initiador(BlockingQueue& queue_e, MultipleProxy& proxy_e, 
	std::map<int, PlayerInfo*>& players_e, std::map<std::string, Room*>& rooms_e, std::mutex& mutex):
		queue(queue_e), not_playing(proxy_e), players(players_e), rooms(rooms_e), rooms_mutex(mutex){
	
	this->keep_working = true;
}

Initiador::~Initiador(){
}

void Initiador::disconnectFromRoom(int player_id, Room* room){
	room->erase(player_id);
	std::string room_name = room->getName(); //cambiar a id
	if (room->cantPlayers() == 0){
		if (room->isActive()){
			room->join();
			delete this->playing_rooms.at(room_name);
			this->playing_rooms.erase(room_name);
		} else {
			this->not_playing.sendRoomDeletion(room_name);
			delete room;
			this->rooms.erase(room_name);
		}
	} else if (!room->isActive()){
		this->not_playing.sendRoomPlayersChange(room_name, room->cantPlayers());
	}
	this->players[player_id]->setRoom(nullptr);
}

void Initiador::sendAllRoomsInfo(int player_id){
	Proxy* proxy = this->players[player_id]->receiver->getProxy();
	this->not_playing.add(player_id, proxy);
	std::map<std::string, Room*>::iterator rooms_it = rooms.begin();
	for (; rooms_it != rooms.end(); ++rooms_it){
		proxy->sendRoomCreation(rooms_it->first, rooms_it->second->cantPlayers(), 
			rooms_it->second->maxPlayers(), rooms_it->second->mapId());
	}
}

void Initiador::run(){
	bool keep = this->keep_working;
	while (keep){
		char* msj = this->queue.pop();
		int player_id = ntohl(*(reinterpret_cast<int*>(msj + 1)));
		switch (msj[0]){
			case 10:{ //desconeccion
					Room* room = this->players[player_id]->room;
					if (room){
						this->disconnectFromRoom(player_id, room);
					}
					this->players[player_id]->receiver->stop();
					this->players[player_id]->receiver->join();
					delete this->players[player_id]->receiver;
					delete this->players[player_id];
					this->players.erase(player_id);
					this->not_playing.erase(player_id);
					break;
				}
			case 11: {//salida del room					
					std::lock_guard<std::mutex> lock(this->rooms_mutex);
					Room* room = this->players[player_id]->room;
					if (room){
						this->disconnectFromRoom(player_id, room);
						this->sendAllRoomsInfo(player_id);
					}
					break;
			}
			case 12:{ //conexion a una partida
					this->not_playing.erase(player_id);
					int name_len = ntohl(*(reinterpret_cast<unsigned int*>(msj + 5)));
					std::string room_name(msj + 9, name_len);
					
					std::lock_guard<std::mutex> lock(this->rooms_mutex);
					Room* room = this->rooms.at(room_name);
					room->add(player_id, this->players[player_id]->name, 
							this->players[player_id]->receiver->getProxy());
					this->players[player_id]->setRoom(room);
					if (room->cantPlayers() == room->maxPlayers()){
						this->not_playing.sendRoomDeletion(room_name);
						room->start();
						this->rooms.erase(room_name);
						this->playing_rooms.insert(std::pair<std::string, Room*>(room_name, room));
					} else {
						this->not_playing.sendRoomPlayersChange(room_name, room->cantPlayers());
					}
					break;	
				}				
			case 13: {//creacion de una room
					std::cout << "crear room\n";
					unsigned int map_id = ntohl(*(reinterpret_cast<unsigned int*>(msj + 5)));
					std::cout << "map_id: " << map_id << '\n';
					int max_players = ntohl(*(reinterpret_cast<int*>(msj + 9)));
					std::cout << "max_players: " << max_players << '\n';
					int name_len = ntohl(*(reinterpret_cast<unsigned int*>(msj + 13)));
					std::cout << "name_len: " << name_len << '\n';
					std::string room_name(msj + 17, name_len);
					std::cout << room_name << '\n';
					
					Proxy* player_proxy = this->players[player_id]->receiver->getProxy();
					std::lock_guard<std::mutex> lock(this->rooms_mutex);
					if (this->rooms.count(room_name) == 0){
						this->not_playing.erase(player_id);
						Room* room = new Room(room_name, map_id, max_players);
						std::string name = this->players[player_id]->name;
						room->add(player_id, name, player_proxy);
						this->rooms.insert(std::pair<std::string, Room*>(room_name, room));
						this->not_playing.sendRoomCreation(room_name, room->cantPlayers(), 
							room->maxPlayers(), room->mapId());
						this->players[player_id]->setRoom(room);
					} else {
						player_proxy->sendRoomNameError();
					}
					break;
				}
				
		}
		delete[] msj;
		std::lock_guard<std::mutex> lock_keep(this->keep_mutex);
		keep = this->keep_working;
	}
	
}

void Initiador::stop(){
	std::lock_guard<std::mutex> lock(this->keep_mutex);
	this->keep_working = false;
	//to unlock the blocking queue
	char* something = new char[5];
	something[0] = 0;
	this->queue.push(something);
}
