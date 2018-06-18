#include "GameWinnerEvent.h"
#include "../view/SdlScreen.h"

#include <iostream>
#define W_HEIGHT  900
#define W_WIDHT 700

GameWinnerEvent::GameWinnerEvent(int idPlayer,Model& model, mainView& view)
    :idPlayer(idPlayer), model(model), view(view){};

void GameWinnerEvent::process(){
    if (model.isPlayer(this->idPlayer)){
        view.showWinner();
        //TextureManager::Instance().draw("win",0,0,0,  finalScreen.getRenderer());
    }
    else{
        view.showLosser();
        //TextureManager::Instance().draw("lose",0,0,0,  finalScreen.getRenderer());
    }
    
    model.closeComunnication();
}
