#include "WormMoveCommand.h"

WormMoveCommand::WormMoveCommand(int idWorm, const int dir)
    :idWorm(idWorm), dir(dir){}
    
void WormMoveCommand::send(ProxyClient& proxy){
    proxy.sendByte(1);
    proxy.sendInt(idWorm);
    proxy.sendInt(dir);
}