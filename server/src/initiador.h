#include "thread.h"
#include "multiple_proxy.h"
#include "blocking_queue.h"
#include "receiver.h"
#include "room.h"
#include "player_info.h"
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <mutex>

#ifndef __INITIADOR_H__
#define __INITIADOR_H__

class Initiador : public Thread{
	private:
		BlockingQueue& queue;
		MultipleProxy& not_playing;
		std::map<int, PlayerInfo>& players;
		std::map<int, Room*>& rooms;
		std::mutex& mutex;
		std::mutex keep_mutex;
		bool keep_working;
		int room_id = 1;
		
		void disconnectFromRoom(int player_id, int room_id);
	
	public:
		Initiador(BlockingQueue& queue, MultipleProxy& proxy, 
		std::map<int, PlayerInfo>& players, std::map<int, Room*>& rooms, std::mutex& mutex);
		
		~Initiador();
		
		virtual void run();
		
		virtual void stop();
		
		void sendAllRoomsInfo(int player_id, Proxy& proxy);
		
};

#endif
