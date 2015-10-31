#ifndef M4_h
#define M4_h

#include "defined.h"
#include "gun.h"
#include "bullet.h"

class M4: virtual public Gun
{
public:
	M4();
	virtual void nothing();
	virtual void positionWeapon();
	virtual void hideGun();
	virtual void showGun();
	virtual void deleteGun();

protected:
	Bullet bullet[20];
};

#endif