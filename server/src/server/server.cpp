#include "server/server.h"
#include "server/receiver.h"
#include <syslog.h>

#define INFO "[Info] ​%s"

Server::Server(const char* port, std::mutex& syslog_mutex_e, const std::vector<std::string>& maps_e) : 
		syslog_mutex(syslog_mutex_e), maps(maps_e), hall(hall_queue, not_playing, players, mutex){
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
			Socket active = this->socket.accept();
			Receiver receiver(std::move(active), &hall_queue);
			Proxy& proxy = receiver.getProxy();
			const std::string name = proxy.receiveName();
			proxy.sendPlayerId(this->cant_players);
			proxy.sendAvailableMaps(this->maps);
			std::lock_guard<std::mutex> lock_players(this->mutex);
			this->players.insert(std::pair<int, PlayerInfo>(cant_players, std::move(PlayerInfo(std::move(name), std::move(receiver)))));
			//receiver moved so the old reference dont work
			Proxy& new_proxy = this->players.at(cant_players).receiver.getProxy();
			this->hall.sendAllRoomsInfo(cant_players, new_proxy);
			
			this->players.at(cant_players).receiver.start();
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
	std::map<int, PlayerInfo>::iterator it = players.begin();
	for (; it != players.end(); ++it){
		it->second.receiver.stop();
		it->second.receiver.join();
	} 
	this->socket.shutdown();
}
