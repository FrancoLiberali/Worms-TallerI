#include "CreateStageEvent.h"

CreateStageEvent::CreateStageEvent(int widht, int height)
    :widht(widht), height(height){}

void CreateStageEvent::process(){
    view->createStage(widht, height);
}