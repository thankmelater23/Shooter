#include "DarkGDK.h"
#include "defined.h"
#include "sc_collision.h" //loads sparkys collision  plugin
#include "user.h"
#include "m4.h"
#include "pistol.h"


User::User()
{
	obj						= 2;
	health				= 100;
	jumpTimer		= 0; 
	running				= false;
	moving				= false; 
	ground				= 1; 
	gravity				= -0.10f; 
	slope					= 0.5f; 
	radius				= 7.0f;
	jumpHeight		= 7.5f;
	vx					    = 0;
	vy						= 0;
	vz					    = 0;
	secondJump	= 20;
	gunPlace			= 1;
}

void User:: updateCamera(int MouseDiffX, int MouseDiffY)
{
	if(noClip == false /* add this after updateEnemyAnimation*/&& gameOver == false)
	{
		static float CamSpeed = 0.07;
		float RotX;
		float RotY;
		RotX = dbObjectAngleX(sphereCam);
		RotY = dbObjectAngleY(sphereCam);
				
		RotX = dbWrapValue(RotX + float(MouseDiffY) * CamSpeed); //- because when u move the mouse frwd u want him to look up
		RotY = dbWrapValue(RotY + float(MouseDiffX) * CamSpeed); 
				
		//keeps camera from turning upside down and also keeps movement smooth

		dbPositionObject ( sphereCam, dbObjectPositionX(obj), dbObjectPositionY(obj) + 80, dbObjectPositionZ(obj));
		//move the object that follows the character
		dbPositionCamera ( dbObjectPositionX(sphereCam), dbObjectPositionY(sphereCam), dbObjectPositionZ(sphereCam) );//move the camera to the object that follows the character
		// code below makes sure the camera is within boundaries
		// limits downwards point
		if(RotX < 18.0)
		{
				dbRotateObject(3, RotX, RotY, 0);//allows for player to look up and down with the mouse
				dbRotateCamera	 ( dbObjectAngleX(3), dbObjectAngleY(3), dbObjectAngleZ(3) );//rotate the camera to the object that follows the character
				dbRotateObject(2, -RotX, RotY, 0);//allows for player to look up and down with the mouse	 
		}
		else if (RotX > 18.0 && RotX < 60.0)
		{
				dbRotateObject(3, 18.0, RotY, 0);//allows for player to look up and down with the mouse
				dbRotateCamera	 ( dbObjectAngleX(3), dbObjectAngleY(3), dbObjectAngleZ(3) );//rotate the camera to the object that follows the character
				dbRotateObject(2, -18.0, RotY, 0);//allows for player to look up and down with the mouse	
		}
		// limits upwards point
		if(RotX > 345.0 && RotX < 360.0)
		{
				dbRotateObject(3, RotX, RotY, 0);//allows for player to look up and down with the mouse
				dbRotateCamera	 ( dbObjectAngleX(3), dbObjectAngleY(3), dbObjectAngleZ(3) );//rotate the camera to the object that follows the character
				dbRotateObject(2, -RotX, RotY, 0);//allows for player to look up and down with the mouse	
		}
		else if (RotX > 200.0 && RotX < 345.0)
		{	
				dbRotateObject(3, 345.0, RotY, 0);//allows for player to look up and down with the mouse
				dbRotateCamera	 ( dbObjectAngleX(3), dbObjectAngleY(3), dbObjectAngleZ(3) );//rotate the camera to the object that follows the character
				dbRotateObject(2, -345.0, RotY, 0);//allows for player to look up and down with the mouse	
		}	
	}
	else //allows user to roam around the map (noclip)
	{
			static float CamSpeed = 0.1;
			float RotX = dbCameraAngleX();
			float RotY = dbCameraAngleY();

			RotX = dbWrapValue(RotX + float(MouseDiffY) * CamSpeed);
			RotY = dbWrapValue(RotY + float(MouseDiffX) * CamSpeed);
			//keeps camera from turning upside down
			
			if(RotX < 320 && RotX > 100)
			{
				RotX = 320;
			}
			if(RotX < 100 && RotX > 57)
			{
				RotX = 57;
			}
			
			dbRotateCamera(RotX, RotY, 0); //ROTATE CAMERA

			// move around with wasd
		   if (dbKeyState(17)) 
		   { // W Move Forward
			   dbMoveCamera(6);  
		   }
		   if (dbKeyState(31)) 
		   { // S Move Back
			   dbMoveCamera(-6);
		   }
		   if (dbKeyState(30))
		   {  // A strafe left
			   dbMoveCameraLeft(0,6);
		   }
		   if (dbKeyState(32))
		   {  // D strafe Right
			   dbMoveCameraRight(0,6);
		   }
	}


	//Update Later

	//write AFTER updateEnemyAnimations
	//handleDamage();
	//positions the collision box, this is used to receive damage from the enemy 
	//dbPositionObject(myCollisionHitBox, dbObjectPositionX(character), dbObjectPositionY(character), dbObjectPositionZ(character));
	//SC_UpdateObject(myCollisionHitBox);
}

void User::controlcharacter()//by using WASD the character can be controlled
{
	jump(); //handles jumping
	if(noClip == false)
	{
		float oldx;
		float oldy;
		float oldz;

		oldx = dbObjectPositionX(obj);
		oldy = dbObjectPositionY(obj);
		oldz = dbObjectPositionZ(obj);
		
			//if player is jumping or falling then apply 'normal' gravity
			//if not attempt to keep the player stuck to the floor
			if (vy == 0 && jumpTimer == 0 )
			{
				vy = vy + 5*gravity;  //speed at which player falls down
			}
			else vy = vy + gravity;
			float angy;
			//apply gravity, and user changes to movement
			angy = dbObjectAngleY(2);
			
			vx = 0;
			vz = 0;
			// KEYS
			if (dbKeyState(30)) //LEFT A
			{
				//only shows forward animations if both are pressed
				 if(moving == false) //moving is used because keystates work very badly e.g one within another screws up
				 {
					vx = (vx - dbCos(angy))*STRAFF_SPEED; 
					vz = (vz + dbSin(angy))*STRAFF_SPEED; 
				 }
				 else // if forward/backwards is being pressed aswell
				{
					vx = (vx - dbCos(angy))/STRAFF_SPEED; 
					vz = (vz + dbSin(angy))/STRAFF_SPEED; 
				}
			}
			if (dbKeyState(32)) //RIGHT D
				{
					if(moving == false) //moving is used because keystates work very badly e.g one within another screws up
					{
						vx = (vx + dbCos(angy))*STRAFF_SPEED; 
						vz = (vz - dbSin(angy))*STRAFF_SPEED; 
					}
					else // if forward/backwards is being pressed aswell
					{
						vx = (vx + dbCos(angy))/STRAFF_SPEED; 
						vz = (vz - dbSin(angy))/STRAFF_SPEED; 
					 }
				}
			if (dbKeyState(17) && running == false) //W FORWARD
				{
					moving = true;
					//sends first final animation frame, time in millisecs between change of frame, and object to modify
					if(running == false) //only walk if the player is not running
						{
						   vx = (vx + dbSin(angy))*PLYR_FWD_WALK_SPEED;
						   vz = (vz + dbCos(angy))*PLYR_FWD_WALK_SPEED;
						}
				}
				else if (dbKeyState(31)) //S BACKWARDS
				{
					moving = true;
					//sends first final animation frame, time in millisecs between change of frame, and object to modify
					if(running == false)
					{
						vx = (vx - dbSin(angy))*PLYR_BCK_WALK_SPEED;
						vz = (vz - dbCos(angy))*PLYR_BCK_WALK_SPEED;
					}
				}
				else 
				{
					if(running == false)
					{
						moving = false;
					}
				}
				//shift is used to toggle running
				if (dbKeyState(17) && dbKeyState(42))
					{
						 vx = (vx + dbSin(angy))*PLYR_RUN_SPEED;
						 vz = (vz + dbCos(angy))*PLYR_RUN_SPEED;
						 running = true;
					}
					else
					{
						running = false;
					}
					
		//this would be the player's final position without collision
		float x = oldx + vx;
		float y = oldy + vy;
		float z = oldz + vz;
		
		//first handle gravity - seperated from horizontal movement
		//to achieve a more realistic effect
		//Method: simple - cast a sphere vertically down, if it hits the level then
		//                 position the object there (sticky collision) then move 
		//                 on to horizontal movement
		//  more complex - if we were to only use the simple method the player would be 
		//                 allowed to climb almost vertical slopes. Alternative is to
		//                 get the normalY direction to work out how flat the gorund
		//                 below the player is, 0-slope# is flatter, slope#-1 is steeper.
		//                 if it's flat, use sticky collision, if it's steep slide the
		//                 player down the slope. Changing slope# determines how steep the 
		//                 player can climb. NOTE: this also effects stairs.
		int collide = SC_SphereCastGroup( 1, oldx,oldy,oldz, oldx,oldy+vy,oldz, radius,0 );
		
		if ( collide > 0 )
		{
			//how flat is this ground
			float ny = SC_GetCollisionNormalY();
			if ( dbAbs(ny) > slope )
			{
				//FLAT, stick
				oldy = SC_GetStaticCollisionY();
			}
			else
			{
				//STEEP, slide
				x = x - oldx; z = z - oldz;
				oldx = SC_GetCollisionSlideX();
				oldy = SC_GetCollisionSlideY();
				oldz = SC_GetCollisionSlideZ();
				x = x + oldx; z = z + oldz;
			}
			
			//ny#<0 means the player has hit a ceiling rather than a floor
			
			if ( ny > slope )
			{
				//only on ground if standing on flat ground
				ground = 1;
				vy = 0;
			}
			else 
			{
				ground = 0;
				//if player has hit a flat ceiling then stop vy# movement
				if ( ny < -slope ) vy = gravity;
			}
		}
		else
		{
			//nothing below player, not on ground, add vertical speed to player
			oldy = oldy + vy;
			ground = 0;
		}
		
		//jumptimer will decrease only when player is back on ground
		//creates a pause between two successive jumps
		if ( ground == 1 && jumpTimer > 0 ) jumpTimer--;
		
		//handle horizontal movement as sliding
		//player only collides with group 1 (level) objs and moves freely through others
		collide = SC_SphereSlideGroup( 1, oldx,oldy,oldz, x,oldy,z, radius,0 );
		
		if ( collide > 0 )
		{
			//if hit, reposition player, halt movement vector
			x = SC_GetCollisionSlideX();
			oldy = SC_GetCollisionSlideY();
			z = SC_GetCollisionSlideZ();
			vx = 0;
			vz = 0;
			
			//possible code for giving the player a jumping help up stairs...
			//might be useful if slope# is set very high but stairs are still required
			//dy = oldy - SC_GetStaticCollisionY()
			//if ( dy < slope && dy > 0 && ground == 1 ) vy = 0.5;
		}
			//position the character based on what the player pressed
			dbPositionObject( obj,x,oldy,z );
			SC_UpdateObject( obj );
	}
}
void User::jump()
{
	//if player is jumping or falling then apply 'normal' gravity
	//if not attempt to keep the player stuck to the floor
	if ( vy == 0 && jumpTimer == 0 ) vy = vy + 10*gravity; 
	else vy = vy + gravity;

	if ( ground == 1 && jumpTimer > 0 ) jumpTimer--;
	//only jump if on ground, and a certain time after last jump
	if ( ground == 1 ) 
	{
		if ( dbSpaceKey() == 1 && jumpTimer == 0 ) 
		{
			vy = vy + jumpHeight;; //what speed user moves up with jump
			jumpTimer = secondJump;
		}
	}
}
