#include "WormChangeAimEvent.h"

#include <iostream>

WormChangeAimEvent::WormChangeAimEvent(int delta)
	:delta(delta){}
	
void WormChangeAimEvent::process(){
	WormView* wormView = view->getWormView(model->getIdWormSelected());
	wormView->changeAimAngle(delta);
	view->update();
}