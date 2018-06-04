#include "Controller.h"
#include <iostream>

Controller::Controller(Model& model, View& view)
    : model(model), view(view) {}

void Controller::handle(SDL_Event& e) {
    switch (e.type){
        case SDL_QUIT:
				std::cout<<"cerrar" << std::endl;			
				view.close();
				break;
        case SDL_KEYDOWN:{
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) e;
            switch (keyEvent.keysym.sym) {
                case SDLK_LEFT:
                    std::cout <<"move "<<-1<<std::endl;
                    model.KeyWormMove(-1);
                    break;
                case SDLK_RIGHT:
                    std::cout <<"move "<<1<<std::endl;
                    model.KeyWormMove(1);
                    break;
                }
        }
        /*case SDL_MOUSEMOTION:
            std::cout << e.motion.x << "," << e.motion.y << std::endl;
            break;*/
		}
}

