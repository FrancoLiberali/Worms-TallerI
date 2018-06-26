#include "CreateVigaEvent.h"

CreateVigaEvent::CreateVigaEvent(int x, int y, int angle)
    :posx(x), posy(y), angle(angle){}

void CreateVigaEvent::process(){
    view->addViga(posx, posy, angle);
}