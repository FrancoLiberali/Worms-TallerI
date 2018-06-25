#include "CreateVigaEvent.h"

CreateVigaEvent::CreateVigaEvent(int x, int y, int angle)
    :posx(x), posy(y), angle(angle){}

void CreateVigaEvent::process(){
    //printf("Create Viga (%d-%d) |< %d \n", posx, posy, angle);
    view->addViga(posx, posy, angle);
    printf("PROCESAR_EVENTO : crear viga done \n");

}