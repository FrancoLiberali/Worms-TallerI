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
public:
    Controller(Model& model, mainView& view);
    //Maneja todos los eventos del cliente
    void handle(SDL_Event& e);
    void checkMouseState(SDL_Event& e, EventHandler& eventHandler);
};

#endif
