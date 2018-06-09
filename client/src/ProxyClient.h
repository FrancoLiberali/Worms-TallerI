#ifndef _PROXY_CLIENT_H
#define _PROXY_CLIENT_H

#include <string>
#include "common/socket.h"

class ProxyClient {
private:
    Socket sktClient;
    std::string socket;
public:
    ProxyClient(std::string socket);
    ProxyClient(Socket socket);
    ~ProxyClient() noexcept;
    void close();
    void sendInt(int num);
    void sendChar(char bye);
    int receiveInt();
    char receiveChar();

};

#endif