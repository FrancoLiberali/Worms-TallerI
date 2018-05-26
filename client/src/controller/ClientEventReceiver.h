#ifndef _CLIENT_EVENT_RECEIVER_H
#define _CLIENT_EVENT_RECEIVER_H 

#include "../common/Queue.h"
#include "../common/Thread.h"

class ClientEventReceiver : public Thread{
private:
	std::string socket_file;
	//agrgar cola bloqueante;
	Queue& q;
	bool closed;
public:
	ClientEventReceiver(std::string socket, Queue& eventQueue);
	~ClientEventReceiver();
	virtual void run() override;
	void stop();
	bool isClosed() const;
	
};

#endif
