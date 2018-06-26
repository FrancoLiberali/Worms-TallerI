#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>

/**
* @class Sprite
* Clase que wrappea el manejo de sprites para su animación.
*/

class Sprite {
private:
	std::string imageId;
	int width;
	int height;
	int rows;
	int currentRow;

	bool repeat;

	int initFrame;
	int countFrame;

public:
	Sprite();
	//inicializa un sprite de acuerdo si se repite o no, numero de filas, frame de inicio y un id
	Sprite(std::string imageId, int width, int height, int rows, bool repeat, int initFrame = 0);
	Sprite(const Sprite & sprite);	
	~Sprite();
	//actuliza el sprite según el modificador
	void update(int modifier = 0);
	//vuelve al fila de inicio				
	void clean();	
	std::string getImageId();
	int getWidth();
	int getHeight();
	int getRows();
	int getCurrentRow();
	bool isLastFrame();
	bool isInit();
};



#endif