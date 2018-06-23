#include "WormShootCommand.h"

WormShootCommand::WormShootCommand(int idJugador)
    :idJugador(idJugador){}

void WormShootCommand::send(ProxyClient& proxy){
    proxy.sendWormShoot(idJugador);
}