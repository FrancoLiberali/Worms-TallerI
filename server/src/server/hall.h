#include "util/thread.h"
#include "server/multiple_proxy.h"
#include "util/blocking_queue.h"
#include "server/receiver.h"
#include "server/room.h"
#include "server/player_info.h"
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <mutex>

#ifndef __HALL_H__
#define __HALL_H__

class Hall : public Thread{
	private:
		BlockingQueue& queue;
		MultipleProxy& not_playing;
		std::map<int, PlayerInfo>& players;
		std::mutex& mutex;
		std::map<int, Room> rooms;
		std::mutex keep_mutex;
		bool keep_working;
		int room_id = 1;
		
		// Saca al jugador player_id de la sala room_id
		void disconnectFromRoom(int player_id, int room_id);
	
	public:
		// Crea un objeto Hall, el cual es el hilo que se encarga
		// de sacar todos los mensajes que se encolen a la hall queue
		// y realizar las accion que correspondan: crear sala, unirse a una sala,
		// salir de una sala o desconectarse.
		Hall(BlockingQueue& queue, MultipleProxy& proxy, 
		std::map<int, PlayerInfo>& players, std::mutex& mutex);
		
		~Hall();
		
		virtual void run();
		
		virtual void stop();
		
		// Envia al jugador correspondiente al player id
		// la informacion de todos los mapas disponibles
		// via el proxy. 
		// Ademas lo agrega a la lista de jugadores en el hall de partidas
		void sendAllRoomsInfo(const int player_id, Proxy& proxy);
		
};

#endif
