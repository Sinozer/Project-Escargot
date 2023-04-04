#pragma once
#define B(x) S_to_binary_(#x)
/*
? byts :

  "000000  | 000000  | 0000"
  beCollide|canColide|collision

  {
	beCollide part:
		Return if the "object" can be collide or not
		Exemple:
			"000000": completely invicible;
			"100000": Can be touch -> Player;
			"100001": Can be touch-> Player and bullet
	}

	//A voir avec théo si utile

canColide part:
	Return if the "object" can collide or not
	Exemple:
		"000000": Can't collide;
		"100000": Can touch-> Player;
		"100001": Can touch-> Player and bullet


collision part:
	Return on binary what part of the collision box is collide:
		Exemple :
			-'0000' collions = null
			-'1000' collions = up
			-'0100' collions = down
			-'0010' collions = left
			-'0001' collions = right
		Can be cumulate:
			Exemple :
			-'1001' collions = up , right
			-'0110' collions = down ,left
*/
int Collide[] = 
{
	0b000001,//Player
	0b100100,//Enemy
	0b000000,//Collectible
	0b000000,//Box
	0b000000,//Platforme
	0b000000,//Bullet
};
int Collider[] = 
{
	0b000000,//Player
	0b000000,//Enemy
	0b000000,//Collectible
	0b000000,//Box
	0b000000,//Platforme
	0b000000,//Bullet
};
int DirectionCollide[] = {
	0b0000,//Player
	0b0000,//Enemy
	0b0000,//Collectible
	0b0000,//Box
	0b0000,//Platforme
	0b0000,//Bullet
};

enum numBitMask {
	BitMaskPlayer = 0,
	BitMaskEnemy = 1,
	BitMaskCollectible = 2,
	BitMaskBox = 3,
	BitMaskPlatforme = 4,
	BitMaskBullet = 5
};

int* Bitmask[] = {
	 Collide,
	 Collider,
	 DirectionCollide,
};

enum typeBitMask {
	TypeCollide = 0,
	TypeCollider= 1,
	TypeDirectionCollide = 2,
};

/*
How use bitmask:

Bitmask[numBitMask.Player] && Bitmask[numBitMask.Box]


*/