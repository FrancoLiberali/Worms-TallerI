#ifndef __FRAGMENT_INFO_H__
#define __FRAGMENT_INFO_H__

struct FragmentInfo{
	public:
		float x;
		float y;
		int direction;
		float angle;
		int vel;
		int damage;
		int radius;
		
		// Estructura que guarda la informacion necesaria para la creacion de un fragmento de proyectil
		FragmentInfo(float x_e, float y_e, int direction_e, float angle_e, int vel_e, int damage_e,
		int radius_e) : x(x_e), y(y_e), direction(direction_e), angle(angle_e), vel(vel_e), damage(damage_e), radius(radius_e){} 
};

#endif
