#include "StartTurnEvent.h"

#include <string>

StartTurnEvent::StartTurnEvent(int idPlayer, int idWorm, Model& model, mainView& view)
    :playerId(idPlayer), idWorm(idWorm), model(model), view(view){
}

void StartTurnEvent::process(){
    std::string namePlayer = model.getPlayerById(playerId);
    SDL_ShowWindow(view.getScreen().getWindow());
    model.selectWorm(idWorm);
    view.changeTurn(namePlayer, idWorm);
}