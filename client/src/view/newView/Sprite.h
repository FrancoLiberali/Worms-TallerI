#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>
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
	Sprite(std::string imageId, int width, int height, int rows, bool repeat, int initFrame = 0);
	Sprite(const Sprite & sprite);	
	~Sprite();					
	void clean();
	void update(int modifier = 0);
	void setImageId(std::string imageId) {this->imageId = imageId;}
	void setWidth(int width) {this->width = width;}
	void setHeight(int height) {this->height = height;}
	void setRows(int rows) {this->rows = rows;}
	//void setCurrentFrame(int currentFrame) {this->currentFrame = currentFrame;}
	void setCurrentRow(int currentRow) {this->currentRow = currentRow;}
	
	std::string getImageId() {return this->imageId;}
	int getWidth() {return this->width;}
	int getHeight() {return this->height;}
	int getRows() {return this->rows;}
	//int getCurrentFrame() {return this->currentFrame;}
	int getCurrentRow() {return this->currentRow;}
	bool isLastFrame();
};



#endif