#ifndef _PROXY_CLIENT_H
#define _PROXY_CLIENT_H

#include <string>

class ProxyClient {
private:
    std::string& socket;
public:
    ProxyClient(std::string socket);
    ~ProxyClient();
    void sendInt(int num);
    void sendChar(char bye);
    int receiveInt();
    char receiveChar();
    void close();
};

#endif