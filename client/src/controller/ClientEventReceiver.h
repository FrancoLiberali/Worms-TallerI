#ifndef _CLIENT_EVENT_RECEIVER_H
#define _CLIENT_EVENT_RECEIVER_H 

#include "../common/Queue.h"
#include "../common/Thread.h"
#include "../ProxyClient.h"
#include "../model/Model.h"
#include "Event.h"

class ClientEventReceiver : public Thread{
private:
	std::string socket_file;
	Queue<Event*>& q;
	ProxyClient& proxy;
	Model& model;
	bool closed;
public:
	ClientEventReceiver(ProxyClient& proxy, Queue<Event*>& eventQueue, 
						std::string socket, Model& model);
	~ClientEventReceiver();
	virtual void run() override;
	void stop();
	bool isClosed() const;
	
};

#endif
