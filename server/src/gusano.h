#include "Box2D/Box2D.h"
#include "gusano_state.h"
#include <vector>
#include "user_data.h"
#include "multiple_proxy.h"
#include "fake_proxy/mok_proxy.h"
#include <map>
#include <utility>
#include "projectile.h"

#ifndef __GUSANO_H__
#define __GUSANO_H__

class Gusano{
	private:
		b2World& world;
		MultipleProxy& proxy;
		std::vector<std::pair<int, int>>& to_remove_gusanos;
		b2Body* body;
		GusanoState* state;
		//las datas son punteros que los cuerpos del mundo de simulacion
		// tienen asociados para poder reconocerlos a la hora de un contacto
		// y poder llamar a sus metodos. Para mas info ver contact_listener
		UserData* user_data;
		int* foot_sensor_data;
		int* head_sensor_data;
		
		int direction;
		std::vector<float> angles_list;
		std::pair<int, int> number;
		int id;
		int life = 100;
		unsigned int damage_suffered = 0;
		bool head_in_contact = false;
		
		void rotateTo(float angle);
		
	public:
		// Crea un gusano en el mundo
		Gusano(b2World& world_entry, MultipleProxy& proxy_e,
		std::vector<std::pair<int, int>>& to_remove_gusanos_e, float x, float y, float angle);
		
		~Gusano();
		
		// Setea al gusano el numero de player que es el duenio,
		// el numero de gusano que es para ese duenio y su id unica.
		void setId(int player, int number, int id);
		
		// Obtiene la id unica del gusano.
		int getId();
		
		b2Vec2 GetPosition();
		
		float32 GetAngle();
		
		int getDirection();
		
		// Envia por el proxy multiple la posicion de este gusano.
		void sendPosition();
		
		// Mover 0.1m hacia la direccion durante 0.5s.
		// El estado del gusano cambiara a moviendose.
		void move(int dir);
		
		// Cancela cualquier tipo de movimiento que el gusano
		// este realizando si este es invalido a nivel de jugabilidad.
		void cancelMovement();
		
		// Actuliza al gusano luego de una simulacion, 
		// para que pueda determinar el paso del tiempo
		void update();
		
		bool isInactive();
		
		// El gusano salta, su estado cambiara a saltando
		void jump();
		
		// El gusano salta hacia atras, su estado cambiara a saltando
		void backJump();
		
		// El gusano toco el final del mapa por lo que
		// debe ser destruido del juego
		void destroy();
		
		// agrega vida al gusano
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
		
};

#endif
