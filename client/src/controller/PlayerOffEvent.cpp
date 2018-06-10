#include "PlayerOffEvent.h"

PlayerOffEvent::PlayerOffEvent(int idPlayer, Model& model, mainView& view)
    :playerId(idPlayer), model(model), view(view){}

void PlayerOffEvent::process(){
    //model.removePlayer(idPlayer);
}