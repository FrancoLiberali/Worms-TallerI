#ifndef _CLIENT_COMMAND_SENDER
#define _CLIENT_COMMAND_SENDER

#include <string>
#include "../common/Queue.h"
#include "../common/Thread.h"
#include "../model/command/ClientCommand.h"
#include "../ProxyClient.h"

class ProxyClient;
class ClientCommand;

/**
* @class ClientCommmandSender
* Envia (ejecuta) todos los comandos al server, desencola de la cola de comandos
* previamente los comandos fueron encolados por GameControllerProxy
*/
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
	void clean();
};

#endif