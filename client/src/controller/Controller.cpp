#include "Controller.h"
#include <iostream>

Controller::Controller(Model& model, mainView& view)
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
                case SDLK_a:
                    model.WormMove(-1); break;
                case SDLK_d:
                    model.WormMove(1); break;
                case SDLK_c:
                    view.actionMenu(); break;
                case SDLK_SPACE: //Salto adelante
                    model.WormJump(1); break;
                case SDLK_f: //salto atras
                    model.WormJump(-1); break;
                }
        }
        case SDL_MOUSEMOTION:
            //std::cout << e.motion.x << "," << e.motion.y << std::endl;
            break;
        case SDL_MOUSEBUTTONDOWN:
            std::cout << e.motion.x << "," << e.motion.y << std::endl;
            SDL_Point mousePointer = {e.motion.x, e.motion.y};
            if (view.hasClickedMenu(mousePointer)){
                Weapon* weapon = view.retrieveWeaponClicked(mousePointer);
                if (weapon)
                    model.WormWeapon((int)weapon->getId());
            }
            break;
		}        
}

