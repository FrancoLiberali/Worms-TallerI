#include "Box2D/Box2D.h"
#include "game/weapons/regresive_projectile.h"
#include "game/weapons/fragment_projectile.h"
#include "game/game_constants.h"

#ifndef __RED_GRANADE_H__
#define __RED_GRANADE_H__

class RedGranade : public RegresiveProjectile {
	private:
		GameConstants& info;
		std::vector<FragmentInfo>& to_create;
	public:
		// Crea un objeto granada roja que sale disparado.
		RedGranade(b2World& world_entry, int number, float x, float y, int direction, float angle, float power,
		GameConstants& info, std::vector<int>& to_remove_e, std::vector<FragmentInfo>& to_create_e, 
		MultipleProxy& proxy, unsigned int time);
		
		~RedGranade();
		
		// Realiza la explosion basica de una proyectil
		// mas la creacion de fragmentos de proyectil que tambien explotan
		// Este codigo se encuentra repetido con el de fragment_projectile,
		// pero como la granada roja tambien es regresiva, no pude llevarlo a
		// cabo con herencia doble.
		virtual void exploit();
};
#endif
