#include "WormChangeAimEvent.h"

#include <iostream>

WormChangeAimEvent::WormChangeAimEvent(int wormId, int delta)
	:wormId(wormId), delta(delta){
}
	
void WormChangeAimEvent::process(){
	WormView* wormView = view->getWormView(wormId);
	wormView->changeAimAngle(delta);
	view->update();
}