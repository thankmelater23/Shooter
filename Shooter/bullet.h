#ifndef Bullet_h
#define Bullet_h

#include "defined.h"




class Bullet
{

public:
	Bullet();



public:
	int	 bullet;
	int	 graphic;
	bool alive;
	float bulletLife;
	float bulletTimer;
	int bulletSpeedTimer;

};

#endif