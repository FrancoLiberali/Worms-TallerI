#include "WormChangeLifeEvent.h"
#include <iostream>

WormChangeLifeEvent::WormChangeLifeEvent(int id, int life)
	:idWorm(id), newLife(life){
}
	

void WormChangeLifeEvent::process(){
	WormView* wormView = view->getWormView(idWorm);
	wormView->changeLife(newLife);
}