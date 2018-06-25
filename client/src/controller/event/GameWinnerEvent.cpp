#include "GameWinnerEvent.h"

#include <iostream>

GameWinnerEvent::GameWinnerEvent(int idPlayer)
    :idPlayer(idPlayer){};

void GameWinnerEvent::process(){
   /* if (model.isPlayer(this->idPlayer)){
        //view.showWinner();
    }
    else{
        //view.showLosser();
    }
    //model.closeComunnication();*/
}
