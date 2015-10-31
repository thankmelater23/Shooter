#include "defined.h"
#include "DarkGDK.h"
#include "functions.h"
#include "user.h"
#include "sc_collision.h" //loads sparkys collision  plugin
#include "gun.h"
#include "m4.h"
#include "pistol.h"



void loadSettings()
{
	dbSyncOn      ();
	dbSyncRate  (SYNC_RATE);
	dbRandomize (dbTimer());
	SC_Start( ); //starts sparkys
	dbBackdropOff();
	dbAutoCamOff(); //stops stupid ass objects from moving the camera when they are loaded
	dbSetDisplayMode ( /*resolution*/ SCREEN_X, SCREEN_Y, 32 );
	dbMaximizeWindow ( );
}



void loadMap(void)
{
	dbLoadObject("map//BasicMap.dbo", MAP);
	dbLoadImage( "map//floor_tile_dre.bmp", MAP_IMAGE );
	dbTextureObject(MAP ,MAP_IMAGE);
	SC_SetupComplexObject(MAP, 1, 2);
	SC_AllowObjectScaling(MAP);
	dbScaleObject(MAP, MAP_SCALE_X, MAP_SCALE_Y, MAP_SCALE_Z);
	SC_UpdateObject(MAP); //updates the map's collision box

	//load crosshair
	dbLoadImage("images//crosshair.dds", crosshair); //loaded here as no point making a function for it
	dbSprite(crosshair, 0, 0, crosshair); //make a sprite out of the image
	dbScaleSprite(crosshair, 120);//increase sprites size by x%
} 


void loadMaincharacter(User &player)
{
	dbMakeObjectBox(player.obj, 30, 150, 30);
	dbPositionObject(player.obj, dbObjectPositionX(MAP), dbObjectPositionY(MAP)-600, dbObjectPositionZ(MAP)); //places player within map
	SC_SetupObject(player.obj, 1, 2);//used to check collisions against the environment
	dbHideObject(player.obj); //hides the main character as this is a FPS
	
	//make main characters camera, this is a sphere that will work as a camera
	dbMakeObjectSphere	(sphereCam, 20 );//make the object that follows the player, the camera follows this object
	dbScaleObject		(sphereCam, .0001, .0001, .0001 );//scale camera out of view .0001, .0001, .0001
	dbPositionObject	(sphereCam, dbObjectPositionX(player.obj), dbObjectPositionY(player.obj) + 50, dbObjectPositionZ(player.obj) );//position it where it goes
}
void inputKeys() //used to debug and see how things are going, also hook some events
{
	dbHideMouse(); 
	dbPositionMouse(dbScreenWidth()/2,dbScreenHeight()/2);
	//ALLOWS ME TO FLY AROUND THE MAP, made for debugging ...
	if(dbScanCode() == 59 && PressingF1 == false) //when f1 is pressed go into flying mode or get off it
	{
		PressingF1 = true;
		if(noClip == true)
		{
			noClip = false;
		}
		else //change back to character
		{
			noClip = true;
			//makes sure that the third person camera is correct
		}
	}
	//keeps mode from changing if button is held down
	if(dbScanCode() != 59 && PressingF1 == true)
	{
		PressingF1 = false;
	}

}
int findObj()
{
int freeObj=500;
	while (dbObjectExist(freeObj))
	{ 
		freeObj++;
	}
	return freeObj;
}

Gun* changeWeapons(Gun *gun)
{
	if(dbUpKey() || dbDownKey())
	{
	if(dbUpKey() && GUN_PLACE < 2 )
	{
		GUN_PLACE ++;
	}

	if(dbDownKey() && GUN_PLACE > 1)
	{
		GUN_PLACE --;
	}

	switch (GUN_PLACE)
	{

	case 1:
		gun->hideGun();
		gun->deleteGun();
	    gun = new M4;
		gun->positionWeapon();
		gun->showGun();
		return gun;;

	case 2:
		gun->hideGun();
		gun->deleteGun();
	    gun = new Pistol;
		gun->positionWeapon();
		gun->showGun();
		return gun;

	default:
		gun->hideGun();
		gun->deleteGun();
		GUN_PLACE = 1;
		gun = new M4;
		gun->positionWeapon();
		gun->showGun();
		return gun;

	}
	}
	return gun;
}
void infoDisplay(Gun *gun, User *player)
{
	dbSetTextSize(38); //thought that this command would work on its own but doesnt seem to function without being in a loop
	
	//displays ammo
	char ammo[100];
	sprintf_s ( ammo, 200, "Ammo = %d /", gun->currentAmmo);
	dbText (100,150, ammo);

	char remainAmmo[100];
	sprintf_s ( remainAmmo, 200, "%d", gun->remainingAmmo);
	dbText (300,150, remainAmmo);
	//tell users reloading is happening
	int y = dbScreenHeight()/2;
	int x = dbScreenWidth()/2;	
	if(gun->reloading == true)
	{
		dbText(x+60, y-80, "Reloading...");//positions the reloading text just next to the crosshair
	}

	char enemiesAlive[100];
	sprintf_s ( enemiesAlive, 200, "Enemies alive: %d", enemyNumDisplay);
	dbText (100, 200, enemiesAlive);

	char remainingHealth[100];
	sprintf_s ( remainingHealth, 200, "Remaining Health: %d", player->health);
	dbText (100, 250, remainingHealth);

	//Displays crosshair
	dbSprite (crosshair, x-32, y-32, crosshair);//64 x 64 is the size of the image, sprite is the only way to make transparency work from the image
	
	//tell the player he has picked up ammo for 2 seconds 
	if(dbTimer() - informationTimer < 2000 && ammoPickedUp == true)
	{
		dbText (x, y-200, "Picked up ammo");
	}
	else if(dbTimer() - informationTimer > 2000) //stop the text from coming up
	{
		ammoPickedUp = false;
	}
}
int findFreeObject()
{
	int freeObj=100;
	while(dbObjectExist(freeObj) == true)
	{ 
		freeObj++;
	}
	return freeObj;
}
