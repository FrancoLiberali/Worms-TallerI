#include "initiador.h"
#include <arpa/inet.h>
#include <iostream>
#include "blocking_queue.h"

Initiador::Initiador(BlockingQueue& queue_e, MultipleProxy& proxy_e, 
	std::vector<std::pair<std::string, Receiver*>>& players_e, std::map<std::string, Room*>& rooms_e, std::mutex& mutex):
		queue(queue_e), not_playing(proxy_e), players(players_e), rooms(rooms_e), rooms_mutex(mutex){
	
	this->keep_working = true;
}

Initiador::~Initiador(){
}

void Initiador::run(){
	bool keep = this->keep_working;
	while (keep){
		char* msj = queue.pop();
		int player_id = ntohl(*(reinterpret_cast<int*>(msj + 1)));
		switch (msj[0]){
			case 10:{ //desconeccion
					this->players[player_id].second->stop();
					delete this->players[player_id].second;
					this->players.erase(this->players.begin() + player_id);
					this->not_playing.erase(player_id);
					break;
				}
			case 11: {//salida del room
					int name_len = ntohl(*(reinterpret_cast<unsigned int*>(msj + 5)));
					std::string room_name(msj + 9, name_len);
					
					std::lock_guard<std::mutex> lock(this->rooms_mutex);
					this->rooms.at(room_name)->erase(player_id);
					if (this->rooms.at(room_name)->cantPlayers() == 0){
						this->not_playing.sendRoomDeletion(room_name);
						delete this->rooms.at(room_name);
						this->rooms.erase(room_name);
					} else {
						this->not_playing.sendRoomPlayersChange(room_name, this->rooms.at(room_name)->cantPlayers());
					}
					Proxy* proxy = this->players[player_id].second->getProxy();
					this->not_playing.add(player_id, proxy);
					std::map<std::string, Room*>::iterator rooms_it = rooms.begin();
					for (; rooms_it != rooms.end(); ++rooms_it){
						proxy->sendRoomCreation(rooms_it->first, rooms_it->second->cantPlayers(), 
						rooms_it->second->maxPlayers(), rooms_it->second->mapId());
					}
					break;
			}
			case 12:{ //conexion a una partida
					this->not_playing.erase(player_id);
					int name_len = ntohl(*(reinterpret_cast<unsigned int*>(msj + 5)));
					std::string room_name(msj + 9, name_len);
					
					std::lock_guard<std::mutex> lock(this->rooms_mutex);
					Room* room = this->rooms.at(room_name);
					room->add(player_id, this->players[player_id].first, 
							this->players[player_id].second->getProxy());
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
					
					Proxy* player_proxy = this->players[player_id].second->getProxy();
					std::lock_guard<std::mutex> lock(this->rooms_mutex);
					if (this->rooms.count(room_name) == 0){
						this->not_playing.erase(player_id);
						Room* room = new Room(map_id, max_players);
						std::string name = this->players[player_id].first;
						room->add(player_id, name, player_proxy);
						this->rooms.insert(std::pair<std::string, Room*>(room_name, room));
						this->not_playing.sendRoomCreation(room_name, room->cantPlayers(), 
							room->maxPlayers(), room->mapId());
					} else {
						player_proxy->sendRoomNameError();
					}
					break;
				}
			case 14: {//salir de una room activa
					int name_len = ntohl(*(reinterpret_cast<unsigned int*>(msj + 5)));
					std::string room_name(msj + 9, name_len);
					
					std::lock_guard<std::mutex> lock(this->rooms_mutex);
					this->playing_rooms.at(room_name)->erase(player_id);
					if (this->playing_rooms.at(room_name)->cantPlayers() == 0){
						this->playing_rooms.at(room_name)->join();
						delete this->playing_rooms.at(room_name);
						this->playing_rooms.erase(room_name);
					} 
					Proxy* proxy = this->players[player_id].second->getProxy();
					this->not_playing.add(player_id, proxy);
					std::map<std::string, Room*>::iterator rooms_it = rooms.begin();
					for (; rooms_it != rooms.end(); ++rooms_it){
						proxy->sendRoomCreation(rooms_it->first, rooms_it->second->cantPlayers(), 
						rooms_it->second->maxPlayers(), rooms_it->second->mapId());
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
	//cuando sea bloqueante ver como desbloquear la cola
}
