
#include "Asteroid.h"


Asteroid::Asteroid()
{
	posX = posY = 0;
	size = 0;
	collected = visited = precious = false;
}
Asteroid::Asteroid(int x , int y, double size1, bool prec)
{
	posX = x;
	posY = y;
	size = size1;
	collected = false;
	visited = false;
	precious = prec;
}

Asteroid::Asteroid(const Asteroid & other)
{
	posX = other.posX;
	posY = other.posY;
	size = other.size;
	collected = other.collected;
	visited = other.visited;
	precious = other.precious;
}

Asteroid::~Asteroid()
{
}

void Asteroid::setCollected(bool newStat)
{
	collected = newStat;
}

void Asteroid::setVisited(bool vis)
{
	visited = vis;
}


bool Asteroid::getCollected() const
{
	return collected;
}

bool Asteroid::getVisited() const
{
	return visited;
}


bool Asteroid::getPrecious() const
{
	return precious;
}


double Asteroid::getSize() const
{
	return size;
}



