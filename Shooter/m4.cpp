#include "m4.h"
#include "DarkGDK.h"
#include "defined.h"

M4::M4()
{
	obj							 =	M4_GUN;
	maxAmmo			 = 40;
	currentAmmo		 = 40;
	remainingAmmo = 80;
	reloading				  = false;
	click						  = M4_CLICK;
	gunShot				  = M4_SHOT;
	reloadTimer		   = 800;
	shootingTimer	  = dbTimer();

	dbLoadObject("weapons//m4.dbo", obj);
	dbScaleObject(obj,100, 100, 100); //works in percentages e.g. 10 makes the gun 10 times smaller(10% of full size)
	dbLoadSound("sounds//M4A1 shot.wav", click);
	dbLoadSound("sounds//m4 click.wav",	  gunShot);
	
	
}

 void M4::nothing()
{
	dbText(300, 500, "Mfsdfsdfdsfsdjfhdsfjhsd4");
	dbWaitKey();
}
 void M4::positionWeapon()
{	//positions the m4 at a fps point of view
	if(noClip == false)
	{
		dbPositionObject(obj,dbCameraPositionX(), dbCameraPositionY()-10,dbCameraPositionZ());
		dbRotateObject(obj,-dbCameraAngleX(), dbCameraAngleY()-180,dbCameraAngleZ());
		dbMoveObject(obj, -18);
		dbMoveObjectRight(obj, -7);
	}
}
 void M4:: hideGun()
 {
	 dbHideObject(obj);
 }
 void M4::showGun()
 {
	 dbShowObject(obj);
 }
 void M4::deleteGun()
 {
	 dbDeleteObject(obj);
 }