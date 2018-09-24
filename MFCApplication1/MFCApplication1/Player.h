
// Player.h : header file
//

#pragma once
#include "Point.h"

class Player
{
// Constructor
public:
    Player() { coor.x = 0, coor.y = 0, speed = 6; };

// Methods
    void Move(int xChange, int yChange);
    void Shoot();
    Point Coordinates();
    void SetCoordinates(int x1, int y1);

// Data
    int speed;

private:
    Point coor;

};
