#include "Escenario.h"
#include "TextureManager.h"

Escenario::Escenario(SdlScreen& screen, Camera& camera)
	:screen(screen), camera(camera){}

void Escenario::draw(){
	TextureManager::Instance().draw("sky", -60 - camera.getX(),-60-camera.getY(), 0, screen.getRenderer());
	for (auto vi = vigas.begin(); vi != vigas.end(); vi++)
		(*vi)->draw();
}

void Escenario::addViga(int x, int y, int angle){
	vigas.push_back(new VigaView(x, y, angle, screen,camera));
}
