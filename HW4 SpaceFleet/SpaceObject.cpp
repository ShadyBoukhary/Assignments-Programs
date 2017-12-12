#include "SpaceObject.h"


void SpaceObject::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}


/* getX()
*  gets the X coordinate of the ship
* parameters: none
* return: int                    */
int SpaceObject::getX() const
{
	return posX;
}

/* getX()
*  gets the X coordinate of the ship
* parameters: none
* return: int                    */
int SpaceObject::getY() const
{
	return posY;
}

std::string SpaceObject::getName()
{
	return name;
}