#ifndef functions_h
#define functions_h
#include "player.h"
#include "user.h"
#include "gun.h"


void loadSettings();
void loadMap();
void loadMaincharacter(User &player);
void inputKeys() ;
int findFreeObject();
void objectExist(int obj);
Gun* changeWeapons(Gun *gun);
void infoDisplay(Gun *gun, User *player);

#endif