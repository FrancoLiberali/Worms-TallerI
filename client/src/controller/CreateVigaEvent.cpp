#include "CreateVigaEvent.h"

CreateVigaEvent::CreateVigaEvent(int x, int y, int angle, mainView& view)
    :posx(x), posy(y), angle(angle), view(view){}

void CreateVigaEvent::process(){
    view.addViga(posx, posy, angle);
}