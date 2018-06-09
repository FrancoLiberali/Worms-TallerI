#include "Escenario.h"
#include "newView/TextureManager.h"

Escenario::Escenario(SdlScreen& screen): screen(screen){
}


void Escenario::draw(){
	TextureManager::Instance().draw("viga", 100, 200, 10, screen.getRenderer());
	TextureManager::Instance().draw("viga", 600, 200, -10, screen.getRenderer());
}
