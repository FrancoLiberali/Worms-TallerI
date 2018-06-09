#include "WormChangeStateEvent.h"
#include <iostream>

WormChangeStateEvent::WormChangeStateEvent(int id, int state)
	:wormID(id){
        switch (state){
            case 0: newState = STATIC; break;
            case 1: newState = MOVE; break;
            case 2: newState = JUMP; break;
            case 3: newState = DEAD; break;
        }
    }
	
void WormChangeStateEvent::process(){
	WormView* wormView = view->getWormView(wormID);
	wormView->changeState(newState);
	std::cout<<"Change state "<<std::endl;
}