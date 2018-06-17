#include "Escenario.h"
#include "newView/TextureManager.h"

Escenario::Escenario(SdlScreen& screen):screen(screen){
}

void Escenario::draw(){
	TextureManager::Instance().draw("sky", 0, 0, 0, screen.getRenderer());
	for (auto vi = vigas.begin(); vi != vigas.end(); vi++)
		(*vi)->draw();
}

void Escenario::addViga(int x, int y, int angle){
	vigas.push_back(new VigaView(x, y, angle, screen));
}
