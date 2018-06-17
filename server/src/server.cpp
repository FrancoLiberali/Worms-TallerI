#include "server.h"
#include "receiver.h"
#include <syslog.h>

#define INFO "[Info] ​%s"

Server::Server(const char* port, std::mutex& syslog_mutex_e) : syslog_mutex(syslog_mutex_e){
	this->socket.bind(port);
	
	this->initiador = new Initiador(hall_queue, not_playing, players, rooms, rooms_mutex);
	initiador->start();
	this->keep_accepting = true;
}

Server::~Server(){
}

void Server::run(){
	bool keep = this->keep_accepting;
	while (keep){
		try{
			Receiver* receiver = new Receiver(socket, &hall_queue);
			Proxy* proxy = receiver->getProxy();
			std::string name = proxy->receiveName();
			std::cout << "name: " << name << '\n'; 
			proxy->sendPlayerId(cant_players);
			this->players.insert(std::pair<int, PlayerInfo*>(cant_players, new PlayerInfo(name, receiver)));
			this->not_playing.add(cant_players, proxy);
		
			std::lock_guard<std::mutex> lock_rooms(rooms_mutex);
			std::map<std::string, Room*>::iterator rooms_it = this->rooms.begin();
			for (; rooms_it != this->rooms.end(); ++rooms_it){
				proxy->sendRoomCreation(rooms_it->first, rooms_it->second->cantPlayers(), 
					rooms_it->second->maxPlayers(), rooms_it->second->mapId());
			}
			receiver->start();
			(this->cant_players)++;
		} catch(const std::exception& e){
			std::lock_guard<std::mutex> lock(this->syslog_mutex);
			syslog(LOG_INFO, INFO, e.what());
		}
		std::lock_guard<std::mutex> lock_keep(this->keep_mutex);
		keep = this->keep_accepting;
	}
}

void Server::stop(){
	{
		std::lock_guard<std::mutex> lock(this->keep_mutex);
		this->keep_accepting = false;
	}
	this->initiador->stop();
	this->initiador->join();
	delete this->initiador;
	std::map<std::string, Room*>::iterator rooms_it = this->rooms.begin();
	for (; rooms_it != this->rooms.end(); ++rooms_it){
		//rooms_it->second->stop();
		//rooms_it->second->join();//para las que se estan jugando detener el juego
		delete rooms_it->second;
	}
	std::map<int, PlayerInfo*>::iterator it = players.begin();
	for (; it != players.end(); ++it){
		it->second->receiver->stop();
		it->second->receiver->join();
		delete it->second->receiver;
		delete it->second;
	} 
	this->socket.shutdown();
}
