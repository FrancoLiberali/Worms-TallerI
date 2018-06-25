#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "../model/Model.h"
#include "../view/mainView.h"
#include "EventHandler.h"

/**
* @class Controller
* Permite la captura de eventos del cliente
* para luego procesarlas con el EventHandler
*/
class Controller {
private:
    Model& model;
    mainView& view;
    int power = false;
    bool playing = true;
public:
    Controller(Model& model, mainView& view);
    //Maneja todos los eventos del cliente
    void handle(SDL_Event& e);
    
    //valida el estado del mouse. Para saber si hay que mover la camara
    void checkMouseState(SDL_Event& e, EventHandler& eventHandler);

    //
    bool isPlaying();
};

#endif
