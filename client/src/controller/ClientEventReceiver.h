#ifndef _CLIENT_EVENT_RECEIVER_H
#define _CLIENT_EVENT_RECEIVER_H 

#include "../common/Queue.h"
#include "../common/Thread.h"
#include "Event.h"

class ClientEventReceiver : public Thread{
private:
	std::string socket_file;
	Queue<Event*>& q;
	bool closed;
public:
	ClientEventReceiver(std::string socket, Queue<Event*>& eventQueue);
	~ClientEventReceiver();
	virtual void run() override;
	void stop();
	bool isClosed() const;
	
};

#endif
