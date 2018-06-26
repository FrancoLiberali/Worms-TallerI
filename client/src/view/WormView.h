#ifndef _WORM_VIEW_
#define _WORM_VIEW_ 

#include "SdlScreen.h"
#include "WormStateAndWeapon.h"
#include "Sprite.h"
#include "TextView.h"
#include "AimView.h"
#include "Camera.h"
#include "PowerView.h"
#include <map>

/**
* @class WormView
* Clase de la vista de un gusano.
*/

class WormView {
private:
	SdlScreen* screen;
	int id, x, y, angle;
	SDL_RendererFlip flip;

	WormState state;

	Sprite* currentSprite;
	std::map<std::string, Sprite> sprites;

	int currentLife;
	int widhtLife100;
	int widhtLifeCurrent;
	TextView life;

	WeaponId weaponId;
	AimView aim;
	Camera& camera;
	PowerView power;

	bool selected;
	bool focus;

	bool alive;
	SDL_Texture* usuarioTexture;
	int idOwner;
	std::string playerName;
	//metodo privado de dibujado
	void draw();
	int getXCenter();
	int getYCenter();
public:
	WormView(int idWorm, int idOwner, Camera& camera);
	void load(int x, int y, SdlScreen* window);
	~WormView();
	//metodo principal de toda vista
	void update();

	int getX();
	int getY();
	bool isCurrWeapon(WeaponId id);

	//metodos que modifican la vista del worm
	void setPlayerName(std::string& player);
	void changeLife(int newLife);
	void changeAimAngle(int delta);
	void selectWeapon(WeaponId idWapon);
	void onFocus();
	void offFocus();
	void select();
	void unselect();
	void upatePower();
	void useWeapon();
	void useTelederigido();
	void changeState(WormState newState);
	void setDirection(int dir);
	void setAngle(int angle);
	void setPos(int x, int y);
};

#endif