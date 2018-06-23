#include "ChangeCountDownCommand.h"


ChangeCountDownCommand::ChangeCountDownCommand(int idJugador, const int time)
    :idJugador(idJugador), time(time){}

void ChangeCountDownCommand::send(ProxyClient& proxy){
    proxy.sendCountDown(idJugador, time);
}