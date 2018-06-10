#include "CreateVigaEvent.h"

CreateVigaEvent::CreateVigaEvent(int x, int y, int angle, mainView& view)
    :posx(x), posy(y), angle(angle), view(view){}

void CreateVigaEvent::process(){
    printf("Create Viga (%d-%d) |< %d \n", posx, posy, angle);
    view.addViga(posx, posy, angle);
}