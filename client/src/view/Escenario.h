#ifndef _ESCENARIO_H
#define _ESCENARIO_H 

#include "newView/SdlScreen.h"
#include <list>
#include "VigaView.h"

class Escenario{
	SdlScreen& screen;
	VigaView* viga;
	std::list<VigaView*> vigas;
public:
	Escenario(SdlScreen& screen);
	void draw();
	void build();
	void addViga(int x, int y, int angle);
};
#endif