#ifndef _ESCENARIO_H
#define _ESCENARIO_H 

#include "newView/SdlScreen.h"
#include <list>

class Escenario{
	SdlScreen& screen;
public:
	Escenario(SdlScreen& screen);
	void draw();
	void build();
};
#endif