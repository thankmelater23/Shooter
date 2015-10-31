#ifndef defined_h
#define defined_h




//Game Settings
#define SYNC_RATE 60

//Sizes
#define MAP_SCALE_X 150
#define MAP_SCALE_Y 100
#define MAP_SCALE_Z 150

//Screen info
#define SCREEN_X 1920
#define SCREEN_Y 1280

//Objects
#define MAP               1
// User	Obj				 = 2
#define sphereCam 3
#define BULLET		5
//Guns
#define	M4_GUN			 70
#define PISTOL_GUN  71



//Images
#define  MAP_IMAGE  1
#define crosshair          3
#define PISTOL_GRAPHIC  71



//Sound
#define M4_SHOT 1
#define M4_CLICK 2
#define PISTOL_CLICK 3
#define PISTOL_SHOT 4


//Enemies
#define MAX_EN 20



//Player
#define PLYR_FWD_WALK_SPEED 4.5
#define PLYR_BCK_WALK_SPEED   3.2
#define PLYR_RUN_SPEED				  6.2
#define STRAFF_SPEED						  3.2



//Game Status
extern bool gameOver;
extern bool noClip;
extern bool PressingF1;
extern int GUN_PLACE;
extern bool ammoPickedUp;
extern int enemyNumDisplay;
extern int informationTimer;


#endif