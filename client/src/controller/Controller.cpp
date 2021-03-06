#include "Controller.h"
#include "MouseState.h"
#include "../view/WormStateAndWeapon.h"

#include <iostream>

#define SALTO 1

Controller::Controller(Model& model, mainView& view)
    : model(model), view(view) {}

void Controller::handle(SDL_Event& e) {
    switch (e.type){
        case SDL_QUIT: //cerrar la ventana principal
				view.close();
                playing = false;
                model.closeComunnication();
				break;
        case SDL_KEYDOWN:{
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) e;
            switch (keyEvent.keysym.sym) {
                case SDLK_LEFT: //mover
                    model.WormMove(-1); break;
                case SDLK_RIGHT:
                    model.WormMove(1); break;
                case SDLK_m: //mostrar u ocultar menú de armas
                    view.actionMenu(); break;
                case SDLK_RETURN: //Salto adelante
                    model.WormJump(SALTO); break;
                case SDLK_BACKSPACE: //salto atras
                    model.WormJump(-SALTO); break;
                case SDLK_UP: //cambio en la mira
                    model.AimChangeAngle(1); break;
                case SDLK_DOWN:
                    model.AimChangeAngle(-1); break;
                case SDLK_SPACE:{//carga de barra de poder
                    model.chargePower();
                    WormView* worm = view.getWormView(model.getIdWormSelected());
                    worm->upatePower();
                    view.update();
                    break;
                }
                case SDLK_1: model.countDown(1); break;//cuenta regresiva para explosión
                case SDLK_2: model.countDown(2); break;
                case SDLK_3: model.countDown(3); break;
                case SDLK_4: model.countDown(4); break;
                case SDLK_5: model.countDown(5); break;  
            }
            break;
        }
        case SDL_KEYUP:{//dejar de cargar y disparar
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) e;
            if (keyEvent.keysym.sym == SDLK_SPACE){
                    model.WormShoot();
                    view.WormShoot(model.getIdWormSelected());
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN:{
            //veo si clickeo el menu
            SDL_Point mousePointer = {e.motion.x, e.motion.y};
            if (view.hasClickedMenu(mousePointer)){
                Weapon* weapon = view.retrieveWeaponClicked(mousePointer);
                if (weapon)
                    model.WormWeapon((int)weapon->getId());
            }else{
                //envio el mensaje de teledirigido
                int x = e.motion.x + view.getCamera().getX();
                int y = e.motion.y + view.getCamera().getY();
                model.teledirigido(x, y);
            }
            break;
        }
	}
}

void Controller::checkMouseState(SDL_Event& e, EventHandler& eventHandler){
    if (e.type == SDL_MOUSEMOTION){     
        MouseState mouseState;
        mouseState.handle(e, eventHandler);
    }
    view.update();
}

bool Controller::isPlaying(){
    return playing;
}