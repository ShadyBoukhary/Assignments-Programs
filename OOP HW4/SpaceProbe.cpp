#include "SpaceProbe.h"
#include <sstream>
#include <iomanip>



SpaceProbe::SpaceProbe()
{
	name = "SpaceProbe";
}

SpaceProbe::SpaceProbe(int x, int y) : SpaceCraft(x, y)
{
	name = "SpaceProbe";
}

SpaceProbe::SpaceProbe(const SpaceProbe & other) : SpaceCraft(other)
{
	name = other.name;
}

SpaceProbe::~SpaceProbe()
{
}



void SpaceProbe::collect(int i, AsteroidList& list)
{
	list.setAst(i).setVisited(true);
	if (list.getAst(i).getPrecious())
	{
		visitedAsts.insert(list.getAst(i));
	}
	numVisited++;
	totalVisited++;
}

int SpaceProbe::getClosest(double maxSize, double & distance, const AsteroidList& astList) const
{
	Asteroid closest, next;
	double diffX, diffY, distClosest, distNext;
	bool assumeFirst = false;
	int indexClosest = -1;	// if they've all been visited and user wants
							//more
							// loop through astList and assume the first unVisited asteroid is the
							// closest
	for (int x = 0; x < astList.getSize() && !assumeFirst; x++)
	{
		// get the asteroid 
		Asteroid current = astList.getAst(x);
		// check if it's visited
		if (current.getVisited() == false)
		{
			// assume it is the closest one
			closest = current;
			indexClosest = x;
			assumeFirst = true;
		}
	}
	// calculate distance between the spaceship and the asteroid
	// assumed closest
	diffX = (posX * 10) - (closest.getX() * 10);
	diffY = (posY * 10) - (closest.getY() * 10);
	distClosest = sqrt(pow(diffX, 2) + pow(diffY, 2));

	// search for the closest asteroid
	for (int x = 0; x < astList.getSize(); x++)
	{
		if (!astList.getAst(x).getVisited())
		{
			// calculate distance between ship and next asteroid
			diffX = (posX * 10) - (astList.getAst(x).getX() * 10);
			diffY = (posY * 10) - (astList.getAst(x).getY() * 10);
			distNext = sqrt(pow(diffX, 2) + pow(diffY, 2));
			//compare the distance with the distance between ship and closest
			if (distClosest > distNext)
			{
				// set closest to the next one if it is closer
				closest = astList.getAst(x);
				distClosest = distNext;
				indexClosest = x;
			}
		}
	}
	distance = distClosest;
	return indexClosest;


}

std::string SpaceProbe::to_string()
{
	std::string pos = "(" + std::to_string(getX()) + ", " + std::to_string(getY()) + ")";
	std::ostringstream s;
	s << getName() << std::setw(11) << pos << std::setw(13) << std::to_string(numVisited)
		<< std::endl;

	return s.str();
}
