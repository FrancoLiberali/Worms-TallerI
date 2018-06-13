#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>
class Sprite
{

	std::string imageId;
	int width;
	int height;
	int rows;
	int currentFrame;
	int currentRow;

	bool repeat;

	int fromFrame;
	int toFrame;

	int countFrame;

public:
	Sprite();
	Sprite(std::string imageId, int width, int height, int rows, bool repeat);

	Sprite(const Sprite & sprite);
									
	void clean();
	
	void update();

	~Sprite(void);

	void setImageId(std::string imageId) {this->imageId = imageId;}
	void setWidth(int width) {this->width = width;}
	void setHeight(int height) {this->height = height;}
	void setRows(int rows) {this->rows = rows;}
	void setCurrentFrame(int currentFrame) {this->currentFrame = currentFrame;}
	void setCurrentRow(int currentRow) {this->currentRow = currentRow;}
	
	std::string getImageId() {return this->imageId;}
	int getWidth() {return this->width;}
	int getHeight() {return this->height;}
	int getRows() {return this->rows;}
	int getCurrentFrame() {return this->currentFrame;}
	int getCurrentRow() {return this->currentRow;}
	bool isLastFrame();

};



#endif