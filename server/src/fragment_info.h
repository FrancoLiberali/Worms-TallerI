#ifndef __FRAGMENT_INFO_H__
#define __FRAGMENT_INFO_H__

struct FragmentInfo{
	public:
		float x;
		float y;
		float angle;
		int vel;
		int damage;
		int radius;
		
		FragmentInfo(float x_e, float y_e, float angle_e, int vel_e, int damage_e,
		int radius_e) : x(x_e), y(y_e), angle(angle_e), vel(vel_e), damage(damage_e), radius(radius_e){} 
};

#endif
