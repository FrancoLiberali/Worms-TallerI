#include "thread.h"
#include "proxy.h"
#include "fake_proxy/mok_proxy.h"
#include "protected_queue.h"
#include <mutex>

#ifndef __RECEIVER_H__
#define __RECEIVER_H__

class Receiver : public Thread{
	private:
		ProtectedQueue& queue;
		Proxy* proxy;
		//MokProxy* proxy;
		std::mutex keep_mutex;
		bool keep_receiving = true;
	public:
	
		Receiver(Socket& socket, ProtectedQueue& queue_e);
		
		~Receiver();
		
		Proxy* getProxy();
		
		virtual void run();
		
		virtual void stop();
		
};

#endif
