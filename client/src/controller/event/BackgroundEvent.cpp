#include "BackgroundEvent.h"

#include <iostream>

BackgroundEvent::BackgroundEvent(std::string name)
    :name(name){};

void BackgroundEvent::process(){
    view->setBackground(name);
}
