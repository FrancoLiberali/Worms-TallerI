#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__

#include <string>
#include "receiver.h"
#include "room.h"

struct PlayerInfo{
	public:
		std::string name;
		Receiver receiver;
		int room_id = 0;
		
		PlayerInfo(std::string name_e, Receiver receiver_e) :  name(std::move(name_e)), receiver(std::move(receiver_e)){}
		
		void setRoom(int id){this->room_id = id;}
		
		std::string& getName() {return this->name;}
		
		PlayerInfo(PlayerInfo&& other) : name(std::move(other.name)), receiver(std::move(other.receiver)){}
		
};

#endif
