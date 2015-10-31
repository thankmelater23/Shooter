#ifndef User_h
#define User_h

#include "defined.h"
#include "player.h"
#include "gun.h"



class User:public Player
{
	friend void loadMaincharacter(User &player);

public:
	bool running;
	bool moving;
	int      jumpTimer;
	int	  gunPlace;


public:
	User();
	void updateCamera(int MouseDiffX, int MouseDiffY);
	void controlcharacter();


protected:
	void jump();
};
#endif