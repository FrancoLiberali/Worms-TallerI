#ifndef _GAME_CLIENT_H
#define _GAME_CLIENT_H

#include "ProxyClient.h"
#include <string>

/**
* @class GameClient
* Es la clase que contiene toda la lógica del juego 
* después de la conexión
*/

class GameClient{
private:
    ProxyClient& proxy;
    std::string name;
public:
    GameClient(ProxyClient& proxy, std::string nameClient);
    //método principal del juego, game loop.
    void run();
};

#endif