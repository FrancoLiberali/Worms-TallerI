#include "ChargePowerCommand.h"
  
  
ChargePowerCommand::ChargePowerCommand(int idJugador)
    :idJugador(idJugador){}

void ChargePowerCommand::send(ProxyClient& proxy){
    proxy.sendChargePower(idJugador);
}