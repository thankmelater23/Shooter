#ifndef Pistol_h
#define Pistol_h

#include "gun.h"
#include "defined.h"

class Pistol: virtual public Gun
{
public:
	Pistol();
	virtual void nothing();
	virtual void positionWeapon();
	virtual void hideGun();
	virtual void showGun();
	virtual void deleteGun();

protected:
	Bullet bullet[14];
};

#endif