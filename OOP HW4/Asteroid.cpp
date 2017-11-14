
#include "Asteroid.h"
#include <sstream>
#include <iomanip>

Asteroid::Asteroid()
{
	posX = posY = 0;
	size = 0;
	collected = visited = precious = false;
	name = "Asteroid";
}
Asteroid::Asteroid(int x , int y, double size1, bool prec)
{
	posX = x;
	posY = y;
	size = size1;
	collected = false;
	visited = false;
	precious = prec;
	name = "Asteroid";

}

Asteroid::Asteroid(const Asteroid & other)
{
	posX = other.posX;
	posY = other.posY;
	size = other.size;
	collected = other.collected;
	visited = other.visited;
	precious = other.precious;
	name = other.name;
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

std::string Asteroid::to_string()
{
	std::string pos = "(" + std::to_string(posX) + ", " + std::to_string(posY) + ")";

	std::ostringstream s;
	s << std::setw(17) << pos << std::fixed << std::setprecision(2) << std::setw(9) << size
		<< std::setw(11);
	if (precious)
		s << "YES\n";
	else
		s << "NO\n";

	return s.str();
	//std::string ss = pos + std::string(10, ' ') + std::to_string(size) + std::string(10, ' ');
	//if (precious)
	//	ss += "YES\n";
	//else
	//	ss += "NO\n";
	//return ss;
}
// overload assignment operator for asteroid class
void Asteroid::operator = (const Asteroid& other)
{
	posX = other.posX;
	posY = other.posY;
	size = other.size;
	collected = other.collected;
	visited = other.visited;
	precious = other.precious;
	name = other.name;
}


