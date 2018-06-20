#ifndef _PRE_GAME_MANAGER_H
#define _PRE_GAME_MANAGER_H

#include "mapwindow.h"
#include "ProxyClient.h"

class mapWindow;
class ProxyClient;

class PreGameManager {

private:
    ProxyClient& proxy;
    mapWindow* hall;
public:
    PreGameManager(ProxyClient& proxy);
    void showHall();
    void addMap(std::string nameMap);
};

#endif