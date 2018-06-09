#include "Escenario.h"
#include "newView/TextureManager.h"

Escenario::Escenario(SdlScreen& screen): screen(screen){
	viga = new VigaView(200,200,0, screen);
}


void Escenario::draw(){
	viga->draw();
}

void Escenario::addViga(int x, int y, int angle){
	VigaView* viga = new VigaView(x, y, angle, screen);
}
