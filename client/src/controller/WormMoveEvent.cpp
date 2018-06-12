
#include <iostream>

#include "WormMoveEvent.h"

WormMoveEvent::WormMoveEvent(int id, int x, int y, int dir, int angle)
	:wormID(id),x(x),y(y), dir(dir), angle(angle){}
	
void WormMoveEvent::process(){
	WormView* wormView = view->getWormView(wormID);
	wormView->setPos(x, y);
	wormView->setDirection(dir);
	wormView->setAngle(angle);
	std::cout<<"id "<<wormID<<" dir "<<dir<<" ang "<<angle<<std::endl;
}