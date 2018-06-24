#include "WindChangedEvent.h"
#include <iostream>

WindChangedEvent::WindChangedEvent(int windSpeed)
    :windSpeed(windSpeed){}

void WindChangedEvent::process(){
    view->windChanged(windSpeed);
}