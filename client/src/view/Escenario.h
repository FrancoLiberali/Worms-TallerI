#ifndef _ESCENARIO_H
#define _ESCENARIO_H 

#include "SdlScreen.h"
#include <vector>
#include <string>
#include "VigaView.h"

class Escenario{
	SdlScreen& screen;
	Camera& camera;
	std::vector<VigaView*> vigas;
	std::string background;
	int widht;
	int height;
	int marea;
	std::string getWater();
public:
	Escenario(SdlScreen& screen, Camera& camera);
	void draw();
	void build();
	void addViga(int x, int y, int angle);
	void setDimention(int widht, int height);
	void setBackground(std::string name);
};
#endif