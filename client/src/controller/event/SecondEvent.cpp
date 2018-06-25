#include "SecondEvent.h"
#include <iostream>

SecondEvent::SecondEvent(){}
void SecondEvent::process(){
    view->second();
}