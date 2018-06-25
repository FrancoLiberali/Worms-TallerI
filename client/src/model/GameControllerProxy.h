#ifndef _GAME_CONTROLLER_PROXY_H
#define _GAME_CONTROLLER_PROXY_H

#include "../common/Queue.h"
#include "command/ClientCommand.h"

class ClientCommand;

/**
* @class GameControllerProxy
* Encola los comandos para enviar al server, usa una cola bloqueante.
* Los comandos fueron detectados por el Controller
*/
class GameControllerProxy{
private:
    Queue<ClientCommand *> &queue;
public:
    GameControllerProxy(Queue<ClientCommand *> &queue);
    ~GameControllerProxy();
    void move(const int idJugador, const int direccion);
    void jump(const int idJugador, const int direccion);
    void weapon(const int idJugador, const int idWeapon);
    void aimAngle(const int idJugador, const int delta);
    void chargePower(const int idJugador);
    void shoot(const int idJugador);
    void countDown(const int idJugador, const int time);
    void teledirigido(const int idJugador, const int x, const int y);
    void leaveRoom(const int idJugador);
};

#endif