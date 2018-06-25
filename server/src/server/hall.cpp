#include "server/hall.h"
#include <arpa/inet.h>
#include <iostream>
#include "util/blocking_queue.h"

#define EVENT 0
#define DISCONNECTION 10
#define EXIT 11
#define JOIN 12
#define CREATE 13

#define NO_ROOM 0
#define MIN_MSJ_LEN 5
#define NO_EVENT 0

Hall::Hall(BlockingQueue& queue_e, MultipleProxy& proxy_e, 
	std::map<int, PlayerInfo>& players_e, std::mutex& mutex_e) :
		queue(queue_e), not_playing(proxy_e), players(players_e), mutex(mutex_e){
	
	this->keep_working = true;
}

Hall::~Hall(){
}

void Hall::disconnectFromRoom(int player_id, int room_id){
	Room& room = this->rooms.at(room_id);
	room.erase(player_id);
	if (room.cantPlayers() == 0){
		if (room.isActive()){
			room.join();
		} else {
			this->not_playing.sendRoomDeletion(room_id);
		}
		this->rooms.erase(room_id);
	} else if (!room.isActive()){
		this->not_playing.sendRoomPlayersChange(room_id, room.cantPlayers());
	}
}

void Hall::sendAllRoomsInfo(const int player_id, Proxy& proxy){
	std::map<int, Room>::iterator rooms_it = rooms.begin();
	for (; rooms_it != rooms.end(); ++rooms_it){
		// solo la informacion de la rooms inactivas es enviada
		// ya que son estas las que admiten una nueva coneccion
		if (!rooms_it->second.isActive()){
			proxy.sendRoomCreation(rooms_it->first, rooms_it->second.getName(), rooms_it->second.cantPlayers(), 
				rooms_it->second.maxPlayers(), rooms_it->second.mapName());
		}
	}
	this->not_playing.add(player_id, proxy);
}

void Hall::run(){
	bool keep = this->keep_working;
	while (keep){
		char* msj = this->queue.pop();
		int player_id = ntohl(*(reinterpret_cast<int*>(msj + 1)));
		std::lock_guard<std::mutex> lock(this->mutex);
		switch (msj[EVENT]){
			case DISCONNECTION:{ //desconeccion
					int room_id = this->players.at(player_id).room_id;
					if (room_id){
						this->disconnectFromRoom(player_id, room_id);
					} else {
						this->not_playing.erase(player_id);
					}
					this->players.at(player_id).receiver.stop();
					this->players.at(player_id).receiver.join();
					this->players.erase(player_id);
					break;
				}
			case EXIT: {//salida del room		
					int room_id = this->players.at(player_id).room_id;
					Proxy& proxy = this->players.at(player_id).receiver.getProxy();
					this->players.at(player_id).setRoom(NO_ROOM);
					if (room_id){
						this->disconnectFromRoom(player_id, room_id);
						this->sendAllRoomsInfo(player_id, proxy);
					}
					break;
			}
			case JOIN:{ //conexion a una partida
					int room_id = ntohl(*(reinterpret_cast<int*>(msj + 5)));
					Room& room = this->rooms.at(room_id);
					room.add(player_id, this->players.at(player_id).name, 
							this->players.at(player_id).receiver.getProxy());
					this->players.at(player_id).setRoom(room_id);
					this->not_playing.erase(player_id);
					if (room.cantPlayers() == room.maxPlayers()){
						this->not_playing.sendRoomDeletion(room_id);
						room.start();
					} else {
						this->not_playing.sendRoomPlayersChange(room_id, room.cantPlayers());
					}
					break;	
				}				
			case CREATE: {//creacion de una room
					int max_players = ntohl(*(reinterpret_cast<int*>(msj + 5)));
					int map_len = ntohl(*(reinterpret_cast<int*>(msj + 9)));
					std::string map_name(msj + 13, map_len);
					int name_len = ntohl(*(reinterpret_cast<int*>(msj + 13 + map_len)));
					std::string room_name(msj + 17 + map_len, name_len);
					Proxy& player_proxy = this->players.at(player_id).receiver.getProxy();
					const std::string& name = this->players.at(player_id).getName();
					this->players.at(player_id).setRoom(this->room_id);
					
					Room room(std::move(room_name), std::move(map_name), max_players);
					room.add(player_id, name, player_proxy);
					this->not_playing.erase(player_id);
					this->not_playing.sendRoomCreation(this->room_id, room.getName(), room.cantPlayers(), 
							room.maxPlayers(), room.mapName());
					this->rooms.insert(std::pair<int, Room>(this->room_id, std::move(room)));
					(this->room_id)++;
					break;
				}
				
		}
		delete[] msj;
		std::lock_guard<std::mutex> lock_keep(this->keep_mutex);
		keep = this->keep_working;
	}
	
}

void Hall::stop(){
	std::lock_guard<std::mutex> lock(this->keep_mutex);
	this->keep_working = false;
	//to unlock the blocking queue
	char* something = new char[MIN_MSJ_LEN];
	something[EVENT] = NO_EVENT;
	this->queue.push(something);
	std::map<int, Room>::iterator rooms_it = this->rooms.begin();
	for (; rooms_it != this->rooms.end(); ++rooms_it){
		if (rooms_it->second.isActive()){
			//se debe esperar que las que esten jugando terminen la partida
			rooms_it->second.join();
		}
	}
}
