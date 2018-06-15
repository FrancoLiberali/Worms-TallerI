#include "thread.h"
#include "multiple_proxy.h"
#include "blocking_queue.h"
#include "receiver.h"
#include "room.h"
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
		std::vector<std::pair<std::string, Receiver*>>& players;
		std::map<std::string, Room*>& rooms;
		std::map<std::string, Room*> playing_rooms;
		std::mutex& rooms_mutex;
		std::mutex keep_mutex;
		bool keep_working;
	
	public:
		Initiador(BlockingQueue& queue, MultipleProxy& proxy, 
		std::vector<std::pair<std::string, Receiver*>>& players, std::map<std::string, Room*>& rooms, std::mutex& mutex);
		
		~Initiador();
		
		virtual void run();
		
		virtual void stop();
		
};

#endif
