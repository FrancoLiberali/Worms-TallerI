#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "../model/Model.h"
#include "../view/mainView.h"

class Controller {
private:
    Model& model;
    mainView& view;
public:
    Controller(Model& model, mainView& view);
    void handle(SDL_Event& e);
};

#endif
