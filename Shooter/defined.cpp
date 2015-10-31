#include "defined.h"
#include "DarkGDK.h"

//Game Status
extern bool gameOver = false;
extern bool noClip			 = false;
extern bool PressingF1 = false; //used when going into noclip
extern int GUN_PLACE = 1;
extern bool ammoPickedUp = false;
extern int enemyNumDisplay = 0;
extern int informationTimer = dbTimer(); //used to tell the user specific information for x seconds