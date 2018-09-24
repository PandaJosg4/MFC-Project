
// Projectile.h : header file
//

#pragma once
#include "Point.h"

class Projectile
{
	// Constructor
public:
	Projectile() { coor.x = 0, coor.y = 0, speed = 6, up = false; };

	// Methods
	void Move(int yChange);
	void Shoot();
	Point Coordinates();
	void SetCoordinates(int x1, int y1);

	// Data
	bool up;	// Boolean to track direction of movement (up/down)
	int speed;

private:
	Point coor;

};
