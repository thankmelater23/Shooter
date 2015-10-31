#ifndef Player_h
#define Player_h

class Player
{

	//Friend Globals


protected:
	//Cordinates
	float		 x, y, z, vz, vx, vy;
	bool        ground;
	float         gravity;
	float		 jumpHeight;
	int            slope;
	int            radius;
	int		    secondJump;


protected:
	virtual void jump() = 0;

	//Other vars


public:
	int health;
	int obj;
	int graphic;


	//status
	bool alive;
	bool shotOrHit;


public:
	Player();


};

#endif