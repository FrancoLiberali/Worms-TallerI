#ifndef _CLIENT_COMMAND_SENDER
#define _CLIENT_COMMAND_SENDER

#include <string>
#include "../common/Queue.h"
#include "../common/Thread.h"
#include "../model/ClientCommand.h"
#include "../ProxyClient.h"

class ClientCommandSender : public Thread {
private:
	std::string socket_file;
	Queue<ClientCommand*>& queue;
	bool closed;
	ProxyClient& proxy;
public:
	ClientCommandSender(ProxyClient& proxy, Queue<ClientCommand*>& queue);
	~ClientCommandSender();
	virtual void run() override;
	void stop();
	bool isClosed() const;	
};

#endif