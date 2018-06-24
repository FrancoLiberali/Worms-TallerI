#include "GameWinnerEvent.h"

#include <iostream>

GameWinnerEvent::GameWinnerEvent(int idPlayer,Model& model, mainView& view)
    :idPlayer(idPlayer), model(model), view(view){};

void GameWinnerEvent::process(){
    if (model.isPlayer(this->idPlayer)){
        //view.showWinner();
    }
    else{
        //view.showLosser();
    }
    //model.closeComunnication();
}
