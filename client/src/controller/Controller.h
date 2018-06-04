#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "../model/Model.h"
#include "../view/View.h"

class Controller {
private:
    Model& model;
    View& view;
public:
    Controller(Model& model, View& view);
    void handle(SDL_Event& e);
};

#endif
