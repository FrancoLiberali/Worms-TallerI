#include "thread.h"
#include "mok_proxy.h"
#include <mutex>

#ifndef __RECEIVER_H__
#define __RECEIVER_H__

class MokReceiver : public Thread{
	private:
		MokProxy& proxy;
		std::mutex keep_mutex;
		bool keep_receiving = true;
	public:
	
		MokReceiver(MokProxy& proxy);
		
		~MokReceiver();
		
		virtual void run();
		
		virtual void stop();
		
};

#endif
