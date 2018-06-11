#include "WormJumpCommand.h"
#include <iostream>

WormJumpCommand::WormJumpCommand(int idJugador, const int dir)
                :idJugador(idJugador), dir(dir){}

void WormJumpCommand::send(ProxyClient& proxy){
    if (dir>0)
        proxy.sendJump(idJugador);
    else
        proxy.sendBackJump(idJugador);
}