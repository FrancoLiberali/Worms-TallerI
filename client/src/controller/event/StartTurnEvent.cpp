#include "StartTurnEvent.h"

#include <string>
#include <iostream>

StartTurnEvent::StartTurnEvent(int idPlayer, int idWorm, Model& model, mainView& view)
    :playerId(idPlayer), idWorm(idWorm), model(model), view(view){
}

void StartTurnEvent::process(){
    std::string namePlayer = model.getPlayerById(playerId);
    //SDL_RaiseWindow(view.getScreen().getWindow());
    SDL_ShowWindow(view.getScreen().getWindow());
    model.selectWorm(idWorm);
    view.changeTurn(namePlayer, idWorm);
    printf("PROCESAR_EVENTO comienzo de turno done \n");
    printf("Se muestra la ventana\n");
}