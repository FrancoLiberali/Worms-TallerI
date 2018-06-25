#include "WormChangeLifeEvent.h"
#include <iostream>

WormChangeLifeEvent::WormChangeLifeEvent(int id, int life)
	:idWorm(id), newLife(life){
}
	

void WormChangeLifeEvent::process(){
	WormView* wormView = view->getWormView(idWorm);
	wormView->changeLife(newLife);
	//std::cout<<"Change Life "<<std::endl;
}