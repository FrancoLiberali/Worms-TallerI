#include "Escenario.h"
#include "TextureManager.h"
#include "TextManager.h"

#define INITIAL_X 0
#define INITIAL_Y 0
#define LEVEL_WATER 300
#define SPEED 40

Escenario::Escenario(SdlScreen& screen, Camera& camera)
	:screen(screen), camera(camera), marea(0){}

void Escenario::draw(){
	if (background.length() <= 0)
		return;
	//fondo
	TextureManager::Instance().draw(background, INITIAL_X - camera.getX()
	, INITIAL_Y - camera.getY(), 0, screen.getRenderer(), SDL_FLIP_NONE, widht, height);

	//vigas
	for (auto vi = vigas.begin(); vi != vigas.end(); vi++)
		(*vi)->draw();
	//agua
	std::string id = getWater();
	TextureManager::Instance().draw(id, INITIAL_X-camera.getX(),height-LEVEL_WATER- camera.getY(), 
		0, screen.getRenderer(), SDL_FLIP_NONE, widht, LEVEL_WATER);
}

void Escenario::addViga(int x, int y, int angle){
	vigas.push_back(new VigaView(x, y, angle, screen,camera));
}

void Escenario::setDimention(int widht, int height){
	this->widht = widht;
	this->height = height;
}

void Escenario::setBackground(std::string name){
	background = name;
}

std::string Escenario::getWater(){
	marea++;
	if (marea < SPEED)
		return "marea1";
	else if (marea < 2*SPEED)
		return "marea2";
	else if (marea < 3*SPEED)
		return "marea3";
	else if (marea < 4*SPEED)
		return "marea2";
	if (marea >= 4*SPEED)
		marea = 0;
	return "marea1";
}

