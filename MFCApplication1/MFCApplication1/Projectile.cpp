
// Projectile.cpp : implementation file
//

#include "stdafx.h"
#include "Projectile.h"


// Updates coordinates of player
void Projectile::Move(int yChange)
{
	coor.y += yChange;
}

// Returns coordinates of player
Point Projectile::Coordinates()
{
	return coor;
}

// Sets coordinates of player
void Projectile::SetCoordinates(int x1, int y1)
{
	coor.x = x1;
	coor.y = y1;
}