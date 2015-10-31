#include "pistol.h"
#include "DarkGDK.h"


Pistol::Pistol()
{
	obj							 =	PISTOL_GUN;
	maxAmmo			 = 14;
	currentAmmo		 = 14;
	remainingAmmo = 28;
	reloading				  = false;
	click						  = PISTOL_CLICK;
	gunShot				  = PISTOL_SHOT;
	reloadTimer		   = 500;
	graphic					   = PISTOL_GRAPHIC;

	dbLoadObject("weapons//H-Colt-Static.x", obj);
	dbLoadImage( "weapons//colt.dds", graphic );
	dbTextureObject(obj ,graphic);
	dbScaleObject(obj,10000, 10000, 10000); //works in percentages e.g. 10 makes the gun 10 times smaller(10% of full size)
	dbLoadSound("sounds//M4A1 shot.wav", click);
	dbLoadSound("sounds//m4 click.wav",	  gunShot);

}

void Pistol::positionWeapon()
{	//positions the m4 at a fps point of view
	if(noClip == false)
	{
		dbPositionObject(obj,dbCameraPositionX(), dbCameraPositionY()-15,dbCameraPositionZ() + 5);
		dbRotateObject(obj,-dbCameraAngleX(), dbCameraAngleY(),dbCameraAngleZ());
		dbMoveObject(obj, 25);
		dbMoveObjectRight(obj, 15);
	}
}

void Pistol::nothing()
{
	dbText(300, 500, "pistol4354357463957463574");
	dbWaitKey();
}

 void Pistol:: hideGun()
 {
	 dbHideObject(obj);
 }
 void Pistol::showGun()
 {
	 dbShowObject(obj);
 }
  void Pistol::deleteGun()
 {
	 dbDeleteObject(obj);
 }