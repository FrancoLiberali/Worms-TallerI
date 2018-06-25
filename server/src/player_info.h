#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__

#include <string>
#include "receiver.h"
#include "room.h"

struct PlayerInfo{
	public:
		const std::string name;
		Receiver receiver;
		int room_id = 0;
		
		// Estructura que guarda el nombre y el hilo que recibe todos los mensajes de un jugador
		PlayerInfo(const std::string name_e, Receiver receiver_e) :  name(std::move(name_e)), receiver(std::move(receiver_e)){}
		
		// Agrega a la informacion del jugador que el mismo se encuentra en un sala.
		void setRoom(int id){this->room_id = id;}
		
		// Devuelve el nombre del jugador.
		const std::string& getName() {return this->name;}
		
		PlayerInfo(PlayerInfo&& other) : name(std::move(other.name)), receiver(std::move(other.receiver)){}
		
};

#endif
