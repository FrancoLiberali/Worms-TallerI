#include "initiador.h"
#include <arpa/inet.h>
#include <iostream>
#include "blocking_queue.h"

Initiador::Initiador(BlockingQueue& queue_e, MultipleProxy& proxy_e, 
	std::map<int, PlayerInfo*>& players_e, std::map<int, Room*>& rooms_e, std::mutex& mutex_e) :
		queue(queue_e), not_playing(proxy_e), players(players_e), rooms(rooms_e), mutex(mutex_e){
	
	this->keep_working = true;
}

Initiador::~Initiador(){
}

void Initiador::disconnectFromRoom(int player_id, int room_id){
	Room* room = this->rooms[room_id];
	room->erase(player_id);
	if (room->cantPlayers() == 0){
		if (room->isActive()){
			room->join();
		} else {
			this->not_playing.sendRoomDeletion(room_id);
		}
		delete room;
		this->rooms.erase(room_id);
	} else if (!room->isActive()){
		this->not_playing.sendRoomPlayersChange(room_id, room->cantPlayers());
	}
}

void Initiador::sendAllRoomsInfo(int player_id, Proxy* proxy){
	std::map<int, Room*>::iterator rooms_it = rooms.begin();
	for (; rooms_it != rooms.end(); ++rooms_it){
		if (!rooms_it->second->isActive()){
			proxy->sendRoomCreation(rooms_it->first, rooms_it->second->getName(), rooms_it->second->cantPlayers(), 
				rooms_it->second->maxPlayers(), rooms_it->second->mapId());
		}
	}
	this->not_playing.add(player_id, proxy);
}

void Initiador::run(){
	bool keep = this->keep_working;
	while (keep){
		char* msj = this->queue.pop();
		int player_id = ntohl(*(reinterpret_cast<int*>(msj + 1)));
		std::lock_guard<std::mutex> lock(this->mutex);
		switch (msj[0]){
			case 10:{ //desconeccion
					int room_id = this->players[player_id]->room_id;
					if (room_id){
						this->disconnectFromRoom(player_id, room_id);
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
					int room_id = this->players[player_id]->room_id;
					Proxy* proxy = this->players[player_id]->receiver->getProxy();
					this->players[player_id]->setRoom(0);
					if (room_id){
						this->disconnectFromRoom(player_id, room_id);
						this->sendAllRoomsInfo(player_id, proxy);
					}
					break;
			}
			case 12:{ //conexion a una partida
					int room_id = ntohl(*(reinterpret_cast<int*>(msj + 5)));
					Room* room = this->rooms.at(room_id);
					room->add(player_id, this->players[player_id]->name, 
							this->players[player_id]->receiver->getProxy());
					this->players[player_id]->setRoom(room_id);
					this->not_playing.erase(player_id);
					if (room->cantPlayers() == room->maxPlayers()){
						this->not_playing.sendRoomDeletion(room_id);
						room->start();
					} else {
						this->not_playing.sendRoomPlayersChange(room_id, room->cantPlayers());
					}
					break;	
				}				
			case 13: {//creacion de una room
					std::cout << "crear room\n";
					unsigned int map_id = ntohl(*(reinterpret_cast<unsigned int*>(msj + 5)));
					int max_players = ntohl(*(reinterpret_cast<int*>(msj + 9)));
					int name_len = ntohl(*(reinterpret_cast<unsigned int*>(msj + 13)));
					std::string room_name(msj + 17, name_len);
					std::cout << room_name << '\n';
					
					Proxy* player_proxy = this->players[player_id]->receiver->getProxy();
					std::string& name = this->players[player_id]->getName();
					this->players[player_id]->setRoom(this->room_id);
					
					Room* room = new Room(std::move(room_name), map_id, max_players);
					room->add(player_id, name, player_proxy);
					this->rooms.insert(std::pair<int, Room*>(this->room_id, room));
					this->not_playing.erase(player_id);
					this->not_playing.sendRoomCreation(this->room_id, room->getName(), room->cantPlayers(), 
							room->maxPlayers(), room->mapId());
					(this->room_id)++;
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
