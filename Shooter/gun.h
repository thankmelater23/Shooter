#ifndef Gun_h
#define Gun_h

#include "defined.h"
#include "bullet.h"
#include "user.h"




class Gun
{


public:
	int obj;
	int graphic;
	int gunShot; //used for loading the gun shot sound
	int click ;
	int currentAmmo;
	int maxAmmo;
	int remainingAmmo; //stores w.e. ammo is left to add to the gun
	bool reloading ;
	int reloadTimer;
	int bulletCounter;
	int shootingTimer;

	public:
	virtual void nothing() = 0;
	virtual void positionWeapon() = 0;
	virtual void hideGun() = 0;
	virtual void showGun() = 0;
	virtual void deleteGun() = 0;

};

#endif