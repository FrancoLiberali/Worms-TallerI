#ifndef _PROXY_CLIENT_H
#define _PROXY_CLIENT_H

#include <string>
#include "common/socket.h"

class ProxyClient {
private:
    Socket sktClient;
public:
    ProxyClient(Socket socket);
    ProxyClient();

    ~ProxyClient() noexcept;
    void close();
    void sendInt(int num);
    void sendChar(char bye);
    int receiveInt();
    char receiveChar();

};

#endif