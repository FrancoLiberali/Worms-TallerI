#include "Sprite.h"


Sprite::Sprite():imageId(""), width(0), height(0), rows(0),
	currentFrame(0), currentRow(0), repeat(true), countFrame(10){
}

Sprite::Sprite(std::string imageId, int width, int height, int rows, bool repeat)
					:imageId(imageId), width(width), height(height), rows(rows)
					 ,currentFrame(0), currentRow(0), repeat(repeat), countFrame(10){
}

Sprite::Sprite(const Sprite & sprite)
	:imageId(sprite.imageId), width(sprite.width), 
	 height(sprite.height), rows(sprite.rows), 
	 currentFrame(sprite.currentFrame), currentRow(sprite.currentRow), repeat(sprite.repeat), countFrame(10){
}


Sprite::~Sprite(){
}

void Sprite::clean(){
	this->currentFrame=0;
	this->currentRow=0;
}
	
void Sprite::update() {
	countFrame--;
	if (countFrame != 0)
		return;
	if (repeat){
		this->currentRow++;
		if (this->currentRow >= this->rows){
			this->currentRow = 0;
		}
	} else {
		this->currentRow++;
		if (this->currentRow >= this->rows) {
			this->currentRow = this->rows - 1;
		}
	}
	countFrame = 10;
}

bool Sprite::isLastFrame(){
	return (this->currentRow == this->rows - 1);
}