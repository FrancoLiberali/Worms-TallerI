#include "PlayerLoseEvent.h"

PlayerLoseEvent::PlayerLoseEvent(int idPlayer)
    :playerId(idPlayer){}

void PlayerLoseEvent::process(){
    //Mostrar el boton y desabilitar todo
}