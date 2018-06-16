#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "../model/Model.h"
#include "../view/mainView.h"
#include "EventHandler.h"

class Controller {
private:
    Model& model;
    mainView& view;
    int power = false;
public:
    Controller(Model& model, mainView& view);
    void handle(SDL_Event& e);
    void checkMouseState(SDL_Event& e, EventHandler& eventHandler);
};

#endif
