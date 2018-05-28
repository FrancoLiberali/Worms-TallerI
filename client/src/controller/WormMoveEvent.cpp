
#include <iostream>

#include "WormMoveEvent.h"

WormMoveEvent::WormMoveEvent(int id, int x, int y)
	:wormID(id),x(x),y(y){}
	
void WormMoveEvent::process(){
	WormView* wormView = view->getWormView(wormID);
	wormView->setPos(x, y);
	std::cout<<"id "<<wormID<<"posx "<<x<<"posy "<<y<<std::endl;
}