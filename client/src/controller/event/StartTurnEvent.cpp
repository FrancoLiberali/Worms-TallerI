#include "StartTurnEvent.h"

#include <string>
#include <iostream>

StartTurnEvent::StartTurnEvent(int idPlayer, int idWorm)
    :playerId(idPlayer), idWorm(idWorm){
}

void StartTurnEvent::process(){
    std::string namePlayer = model->getPlayerById(playerId);
    SDL_ShowWindow(view->getScreen().getWindow());
    model->selectWorm(idWorm);
    view->changeTurn(namePlayer, idWorm);
}