#include "Escenario.h"

Escenario::Escenario(Window& window): window(window){
}


void Escenario::draw(){
	/*Las vigas grandes miden 140x20 / 20x140 px */
	LTexture viga1(window);
	if (!viga1.loadFromFile("vigah.png"))
		return;
	viga1.render(100,200); //se renderea pasandole la posicion x, y el angulo en sentido horario(opcional)

	LTexture viga2(window);
	if (!viga2.loadFromFile("vigah.png"))
		return;
	viga2.render(235,212, 10);

	LTexture viga3(window);
	if (!viga3.loadFromFile("vigah.png"))
		return;
	viga3.render(450,212, -10); //se renderea pasandole la posicion x, y el angulo en sentido horario(opcional)

	LTexture viga4(window);
	if (!viga4.loadFromFile("vigah.png"))
		return;
	viga4.render(585,200);

	LTexture agua(window);
	if (!agua.loadFromFile("agua.png"))
		return;
	agua.render(window.getHeight()/8,window.getHeight()-80);
}
