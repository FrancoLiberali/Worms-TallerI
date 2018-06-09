#include "WormJumpCommand.h"

WormJumpCommand::WormJumpCommand(int idJugador, const int dir)
                :idJugador(idJugador), dir(dir){}

void WormJumpCommand::send(ProxyClient& proxy){
    char c = (dir == 1)? 2 : 3;
    proxy.sendChar(c);
    proxy.sendInt(idJugador);
}