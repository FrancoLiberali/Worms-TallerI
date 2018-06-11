#include "ChangeAimCommand.h"

ChangeAimCommand::ChangeAimCommand(int idJugador, const int delta)
                :idJugador(idJugador), delta(delta){}

void ChangeAimCommand::send(ProxyClient& proxy){
    proxy.sendChangeAim(idJugador, delta);
}