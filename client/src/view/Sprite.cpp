#include "Sprite.h"


Sprite::Sprite():imageId(""), width(0), height(0), rows(0), currentRow(0), repeat(true), countFrame(10), initFrame(0){
}
 
Sprite::Sprite(std::string imageId, int width, int height, int rows, bool repeat,int initFrame)
					:imageId(imageId), width(width), height(height), rows(rows)
					 ,currentRow(initFrame), repeat(repeat), countFrame(20), initFrame(initFrame){
}

Sprite::Sprite(const Sprite & sprite)
	:imageId(sprite.imageId), width(sprite.width), 
	 height(sprite.height), rows(sprite.rows), 
	 currentRow(sprite.currentRow), repeat(sprite.repeat), 
	 countFrame(sprite.countFrame), initFrame(sprite.initFrame){
}


Sprite::~Sprite(){
}

void Sprite::clean(){
	this->currentRow = initFrame;
}
	
void Sprite::update(int modifier) {
	if (modifier != 0){
		currentRow += modifier;
		if (currentRow >= rows)
			currentRow = rows - 1;
		else if (currentRow < 0)
			currentRow = 0;
	}
	else{
		countFrame--;
		if (countFrame != 0)
			return;
		currentRow++;
		if (repeat){
			if (currentRow >= rows)
				currentRow = 0;
		} else if (currentRow >= rows){
			currentRow = rows - 1;
		}
		countFrame = 10;
	}
}

bool Sprite::isLastFrame(){
	return (this->currentRow == this->rows - 1);
}

bool Sprite::isInit(){
	return this->currentRow == initFrame;
}