#include "thread.h"
#include "proxy.h"
#include "fake_proxy/mok_proxy.h"
#include "protected_queue.h"
#include <mutex>

#ifndef __RECEIVER_H__
#define __RECEIVER_H__

class Receiver : public Thread{
	private:
		//Proxy& proxy;
		MokProxy& proxy;
		ProtectedQueue& queue;
		std::mutex keep_mutex;
		bool keep_receiving = true;
	public:
		//Receiver(Proxy& proxy_e, ProtectedQueue& queue_e);
		Receiver(MokProxy& proxy_e, ProtectedQueue& queue_e);
		
		~Receiver();
		
		virtual void run();
		
		virtual void stop();
		
};

#endif
