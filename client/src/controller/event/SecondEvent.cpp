#include "SecondEvent.h"
#include <iostream>

SecondEvent::SecondEvent(){}
void SecondEvent::process(){
    view->second();
    printf("Paso un segundo\n");
}