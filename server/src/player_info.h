#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__

#include <string>
#include "receiver.h"
#include "room.h"

struct PlayerInfo{
	public:
		std::string name;
		Receiver* receiver;
		Room* room = nullptr;
		
		PlayerInfo(std::string name_e, Receiver* receiver_e) :  name(name_e), receiver(receiver_e){}
		
		void setRoom(Room* room){this->room = room;}
		
};

#endif
