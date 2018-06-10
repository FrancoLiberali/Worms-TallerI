#include "WormMoveCommand.h"

WormMoveCommand::WormMoveCommand(int idJugador, const int dir)
    :idJugador(idJugador), dir(dir){}
    
void WormMoveCommand::send(ProxyClient& proxy){
    proxy.sendMoveWorm(idJugador, dir);
}