#ifndef _ESCENARIO_H
#define _ESCENARIO_H 

#include "SdlScreen.h"
#include <vector>
#include "VigaView.h"

class Escenario{
	SdlScreen& screen;
	Camera& camera;
	std::vector<VigaView*> vigas;
public:
	Escenario(SdlScreen& screen, Camera& camera);
	void draw();
	void build();
	void addViga(int x, int y, int angle);
};
#endif