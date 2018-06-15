#include "hall.h"

Hall::Hall(MultipleProxy& proxy_e, std::map<std::string, Room*>& rooms_e, std::mutex& mutex): 
	proxy(proxy_e), rooms(rooms_e), rooms_mutex(mutex){
}

Hall::~Hall(){
}

void Hall::run(){
	while(true){
		{ std::lock_guard<std::mutex> lock(this->rooms_mutex);
		std::map<std::string, Room*>::iterator rooms_it = rooms.begin();
		for (; rooms_it != rooms.end(); ++rooms_it){
			if (rooms_it->second->isWaiting()){
				//this->proxy.sendRoomInfo(rooms_it->first, rooms_it->second->cantPlayers(), 
				//rooms_it->second->maxPlayers(), rooms_it->second->mapId());
			}
			else if (rooms_it->second->isFinished()){
				//volver a meter a los jugadores en el hall
			}
		}
		}
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}

void Hall::stop(){
}
