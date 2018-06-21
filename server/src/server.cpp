#include "server.h"
#include "receiver.h"
#include <syslog.h>

#define INFO "[Info] ​%s"

Server::Server(const char* port, std::mutex& syslog_mutex_e, std::vector<std::string>& maps_e) : 
		syslog_mutex(syslog_mutex_e), maps(maps_e), hall(hall_queue, not_playing, players, rooms, mutex){
	this->socket.bind(port);
	
	this->hall.start();
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
			proxy->sendAvailableMaps(this->maps);
			std::lock_guard<std::mutex> lock_players(this->mutex);
			this->players.insert(std::pair<int, PlayerInfo>(cant_players, std::move(PlayerInfo(std::move(name), receiver))));
			this->hall.sendAllRoomsInfo(cant_players, proxy);
			
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
	this->hall.stop();
	this->hall.join();
	std::map<int, Room*>::iterator rooms_it = this->rooms.begin();
	for (; rooms_it != this->rooms.end(); ++rooms_it){
		if (rooms_it->second->isActive()){
			//para las que se estan jugando detener el juego
			//rooms_it->second->stop();
			rooms_it->second->join();
		}
		delete rooms_it->second;
	}
	std::map<int, PlayerInfo>::iterator it = players.begin();
	for (; it != players.end(); ++it){
		it->second.receiver->stop();
		it->second.receiver->join();
		delete it->second.receiver;
	} 
	this->socket.shutdown();
}
