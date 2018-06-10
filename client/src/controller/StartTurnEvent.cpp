#include "StartTurnEvent.h"

#include <string>

StartTurnEvent::StartTurnEvent(int idPlayer, int idWorm, Model& model, mainView& view)
    :playerId(idPlayer), idWorm(idWorm), model(model), view(view){
}

void StartTurnEvent::process(){
    model.selectWorm(idWorm);
    std::string namePlayer = model.getPlayerById(playerId);
    view.changeTurn(namePlayer);
}