#include "WormChangeStateEvent.h"
#include "../../manager/SoundManager.h"
#include <iostream>

WormChangeStateEvent::WormChangeStateEvent(int id, int state)
	:wormID(id){
        newState = static_cast<WormState>(state);
    }
	
void WormChangeStateEvent::process(){
	WormView* wormView = view->getWormView(wormID);
	wormView->changeState(newState);
    if (newState == JUMP)
        SoundManager::Instance().playSound(JUMP_S);
}