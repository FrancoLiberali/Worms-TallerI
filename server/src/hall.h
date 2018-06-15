#include "thread.h"
#include "multiple_proxy.h"
#include "room.h"
#include <vector>
#include <string>
#include <map>
#include <mutex>

#ifndef __HALL_H__
#define __HALL_H__

class Hall : public Thread{
	private:
		MultipleProxy& proxy;
		std::map<std::string, Room*>& rooms;
		std::mutex& rooms_mutex;
		
	public:
		Hall(MultipleProxy& proxy, std::map<std::string, Room*>& rooms, std::mutex& mutex);
		
		~Hall();
		
		virtual void run();
		
		virtual void stop();
};

#endif
	
	
