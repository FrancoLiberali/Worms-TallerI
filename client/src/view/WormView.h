#ifndef _WORM_VIEW_
#define _WORM_VIEW_ 

#include "SdlScreen.h"
#include "WormState.h"
#include "Sprite.h"
#include "SpriteConfigurator.h"
#include "TextureManager.h"
#include "TextView.h"
#include "AimView.h"
#include "Camera.h"
#include "PowerView.h"
#include <map>

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

	WeaponId weaponId;
	AimView aim;
	Camera& camera;
	PowerView power;

	bool selected;
	bool focus;

	bool alive;
	TextView labelUsuario;
	int idOwner;

	void draw(int idPlayerTurn);
	int getXCenter();
	int getYCenter();
public:
	WormView(int idWorm, int idOwner, Camera& camera);
	void setPlayerName(std::string player);
	~WormView();
	void selectWeapon(WeaponId idWapon);
	void load(int x, int y, SdlScreen* window);
	void setPos(int x, int y);
	int getX();
	int getY();
	void update(int idPlayer);
	void changeState(WormState newState);
	void setDirection(int dir);
	void setAngle(int angle);
	void changeLife(int newLife);
	void changeAimAngle(int delta);
	void onFocus();
	void offFocus();
	void select();
	void unselect();
	void upatePower();
	void useWeapon();
	void useTelederigido();
	bool isCurrWeapon(WeaponId id);
};

#endif