#ifndef resources_h
#define resources_h
#include "DarkGDK.h"
#include "defined.h"



void loadResources()
{
	//OBJECTS
	//Map
	dbLoadObject("map//BasicMap.dbo", MAP);
	//M$


	//IMAGES
	//MAP
	dbLoadImage( "map//floor_tile_dre.bmp", MAP_IMAGE );//Graphic
	//CROSSHAIR
	dbLoadImage("images//crosshair.dds", crosshair); //loaded here as no point making a function for it
	//BULLETS
	//M4 Bullet
	dbLoadObject("weapons//bullet.dbo", BULLET);//Graphic



	//SOUNDS
	//M4
}

#endif