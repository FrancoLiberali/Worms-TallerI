#ifndef _ESCENARIO_H
#define _ESCENARIO_H 

#include "newView/SdlScreen.h"
#include <vector>
#include "VigaView.h"

class Escenario{
	SdlScreen& screen;
	std::vector<VigaView*> vigas;
public:
	Escenario(SdlScreen& screen);
	void draw();
	void build();
	void addViga(int x, int y, int angle);
};
#endif