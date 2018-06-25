#include "Box2D/Box2D.h"
#include "game/gusano/gusano_state.h"
#include <vector>
#include "server/multiple_proxy.h"
#include <map>
#include <utility>
#include "game/weapons/projectile.h"
#include "game/gusano/gusano_body.h"

#ifndef __GUSANO_H__
#define __GUSANO_H__

#define GUSANO_INDICATOR 1

class Gusano{
	private:
		b2World& world;
		MultipleProxy& proxy;
		std::vector<std::pair<int, int>>& to_remove_gusanos;
		GusanoBody body;
		GusanoState* state;
		
		int direction;
		std::vector<float> angles_list;
		std::pair<int, int> number;
		int id;
		int life;
		unsigned int damage_suffered = 0;
		bool head_in_contact = false;
		UserData user_data;
		
		// Rota el cuerpo del gusano al angulo angle
		void rotateTo(float angle);
		
	public:
		// Crea un gusano en el mundo en la posicion x,y
		// con un angulo angle y una vida life.
		Gusano(b2World& world_entry, MultipleProxy& proxy_e,
		std::vector<std::pair<int, int>>& to_remove_gusanos_e, float x, float y, float angle, int life_e);
		
		Gusano(Gusano&& other);
		Gusano& operator=(Gusano&& other);
		
		~Gusano();
		
		// Setea al gusano el numero de player que es el duenio,
		// el numero de gusano que es para ese duenio y su id unica.
		void setId(int player, int number, int id);
		
		// Obtiene la id unica del gusano.
		int getId();
		
		// Devuelve el vector posicion del gusano
		b2Vec2 GetPosition();
		
		// Devuelve el angulo en el que se encuentra el gusano.
		float32 GetAngle();
		
		// Devuelve la direccion en la que mira el gusano:
		// -1: izquierda, 1:derecha
		int getDirection();
		
		// Envia por el proxy multiple la posicion de este gusano.
		void sendPosition();
		
		// Mover 0.1m hacia la direccion durante 0.5s.
		// El estado del gusano cambiara a moviendose.
		void move(int dir);
		
		// Actualiza al gusano luego de una simulacion, 
		// para que pueda asimilar el paso del tiempo.
		void update();
		
		// Devuelve true si el gusano esta inactivo.
		bool isInactive();
		
		// El gusano salta un metro hacia adelante
		// y medio metro hacia arriba.
		// Su estado cambiara a saltando hasta que toque el suelo nuevamente
		void jump();
		
		// El gusano salta hacia atras 0.2 y 1.2 metros de alto
		// Su estado cambiara a saltando hasta que toque el suelo nuevamente
		void backJump();
		
		// Cancela cualquier tipo de movimiento que el gusano
		// este realizando si este es invalido a nivel de jugabilidad.
		void cancelMovement();
		
		// Destuir el gusano ya sea porque toco el final del mapa 
		// o porque se quedo sin vida.
		void destroy();
		
		// Agrega vida al gusano
		void addLife(unsigned int life);
		
		// dismuye la vida del gusano. Si esta 
		// llega a cero el gusano es destruido del modelo.
		void sufferDamage(unsigned int damage);
		
		// Devuelve true si el gusano fue herido en la ultima simulacion
		bool gotDamaged();
		
		// El gusano a sufrido un contacto con el suelo en sus pies
		void newContact(float ground_angle);
		
		// El gusano a sufrido un contacto con el suelo en su cabeza
		void headContact();
		
		// El gusano ha dejado mantener un contacto con en suelo en sus pies.
		void finishContact(float ground_angle);
		
		// El gusano ha dejado mantener un contacto con en suelo en su cabeza
		void headFinishContact();
		
		// El gusano estaba cerca de una explosion y por lo tanto debe
		// ser herido y sufrir fuerzas repulsivas.
		void applyExplotion(b2Vec2 apply_point, float damage, b2Vec2 impulse);
		
		// El gusano se teletransporta la nueva posicion
		// Pre: la posicion esta vacia.
		void teleport(b2Vec2 new_position);
		
};

#endif
