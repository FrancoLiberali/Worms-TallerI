#include "socket.h"
#include "proxy.h"
#include "multiple_proxy.h"
//#include "hall.h"
#include "protected_queue.h"
#include "receiver.h"
#include "initiador.h"
#include <string>
#include <vector>
#include <utility>
#include <iostream>

#define EXIT 'q'

int main(int argc, char** argv) {
	if (argc < 2){
		return 1;
	}
	Socket socket;
	socket.bind(argv[1]);
	std::vector<std::pair<std::string, Receiver*>> players;
	MultipleProxy not_playing;
	ProtectedQueue hall_queue;
	std::map<std::string, Room*> rooms;
	std::vector<Room*> playing_rooms;
	std::mutex rooms_mutex;
	Initiador initiador(hall_queue, not_playing, players, rooms, playing_rooms, rooms_mutex);
	initiador.start();
	
	//Hall hall(not_playing, playing_rooms, rooms_mutex);
	//hall.start();
	int cant_players = 0;
	while (true){
		Receiver* receiver = new Receiver(socket, &hall_queue);
		Proxy* proxy = receiver->getProxy();
		std::string name = proxy->receiveName();
		std::cout << "name: " << name << '\n'; 
		proxy->sendPlayerId(cant_players);
		players.push_back(std::pair<std::string, Receiver*>(name, receiver));
		not_playing.add(cant_players, proxy);
		
		std::lock_guard<std::mutex> lock(rooms_mutex);
		std::map<std::string, Room*>::iterator rooms_it = rooms.begin();
		for (; rooms_it != rooms.end(); ++rooms_it){
			proxy->sendRoomCreation(rooms_it->first, rooms_it->second->cantPlayers(), 
				rooms_it->second->maxPlayers(), rooms_it->second->mapId());
		}
		receiver->start();
		cant_players++;
	}
	//hall.stop();
	return 0;
}
