#include "DarkGDK.h"
#include "defined.h"
#include "functions.h"
#include "player.h"
#include "user.h"
#include "enemy.h"
#include "gun.h"
#include "m4.h"
#include "pistol.h"
#include "sc_collision.h" //loads sparkys collision  plugin

using namespace std;


void DarkGDK ( void )
{
	User andre;
	loadSettings();
	loadMap();
	loadMaincharacter(andre);
	Gun *currGun = new M4();


	while ( LoopGDK ( ) )
	{
		andre.updateCamera(dbMouseMoveX(), dbMouseMoveY());
		currGun = changeWeapons(currGun);
		currGun->positionWeapon();
		andre.controlcharacter();
		inputKeys();
		infoDisplay(currGun, &andre);

		dbSync();
	}

	delete currGun;
	return;
}