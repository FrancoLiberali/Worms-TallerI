#ifndef _CLIENT_COMMAND
#define _CLIENT_COMMAND

#include "../ProxyClient.h"

class ClientCommand {
public:
	virtual void send(ProxyClient& proxy) = 0;
};

#endif