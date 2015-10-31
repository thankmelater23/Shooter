/*

void bulletClone(Bullet *bull[], int num);

void Gun::bulletClone(Bullet bull[], int numOfBull)
{
	for(int i = 0; i < numOfBull; i++)
	{
		dbMakeObjectSphere(bull[i].bullet, 3); //makes a small sphere to use for collision against the enemies later on

		dbCloneObject(bull[i].graphic, BULLET);//this is the bullet that leaves the gun, used just for appearences
		
		bull[i].alive = 0;
		bull[i].bulletLife = dbTimer();
		bull[i].bulletTimer = 800;

		dbHideObject(bull[i].bullet); //hide bullet once its created
		dbHideObject(bull[i].graphic);
		SC_SetupObject(bull[i].bullet, 0, 1); //add the bullet to the collision system
	}
}

*/
