

#include "Asteroid.h"


Asteroid::Asteroid()
{
	//pos = new Position(0, 0);
	posX = posY = 0;
	size = 0;
	status = false;
}
Asteroid::Asteroid(int x , int y, double size1)
{
	//pos = new Position(x, y);
	posX = x;
	posY = y;
	size = size1;
	status = false;
}

Asteroid::Asteroid(const Asteroid & other)
{
	posX = other.posX;
	posY = other.posY;
	size = other.size;
	status = other.status;
}

Asteroid::~Asteroid()
{
	//delete this->pos;
	//pos = 0;
}

void Asteroid::setStatus(bool newStat)
{
	status = newStat;
}

bool Asteroid::getStatus() const
{
	return status;
}

//Position* Asteroid::getPosition() const
//{
//	return pos;
//}
int Asteroid::getX() const
{
	return posX;
}

int Asteroid::getY() const
{
	return posY;
}

double Asteroid::getSize() const
{
	return size;
}



