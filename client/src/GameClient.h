#ifndef _GAME_CLIENT_H
#define _GAME_CLIENT_H

#include "ProxyClient.h"
#include <string>

class GameClient{
private:
    ProxyClient& proxy;
    std::string name;
public:
    GameClient(ProxyClient& proxy, std::string nameClient);
    void run();
};

#endif