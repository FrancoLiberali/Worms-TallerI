#include "WormJumpCommand.h"

WormJumpCommand::WormJumpCommand(int idJugador, const int dir)
                :idJugador(idJugador), dir(dir){}

void WormJumpCommand::send(ProxyClient& proxy){
    proxy.sendJump(idJugador, dir);
}