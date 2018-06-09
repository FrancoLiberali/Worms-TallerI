#include "WormMoveCommand.h"

WormMoveCommand::WormMoveCommand(int idJugador, const int dir)
    :idJugador(idJugador), dir(dir){}
    
void WormMoveCommand::send(ProxyClient& proxy){
    proxy.sendChar(1);
    proxy.sendInt(idJugador);
    proxy.sendInt(dir);
}