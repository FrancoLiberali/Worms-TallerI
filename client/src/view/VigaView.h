#ifndef _VIGA_VIEW_H_
#define _VIGA_VIEW_H_

class VigaView {
private:
    int x;
    int y;
	int getXCenter();
	int getYCenter();
    
public:
    VigaView(int posX, int posY);
    ~VigaView();
    void draw();
};
#endif