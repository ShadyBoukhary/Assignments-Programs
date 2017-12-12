#include "SpaceCraft.h"

int SpaceCraft::totalCollected = 0;
int SpaceCraft::totalVisited = 0;
int SpaceCraft::toCollect = 0;
int SpaceCraft::toVisit = 0;
AsteroidList SpaceCraft::visitedAsts = AsteroidList();

// Default Construcor
SpaceCraft::SpaceCraft()
{
	posX = 0;
	posY = 0;
	direction = "Port";
	numVisited = 0;
	totalDistance = 0;
	name = "SpaceCraft";
}
// Parametrized Constructor
SpaceCraft::SpaceCraft(int x, int y)
{
	posX = x;
	posY = y;
	direction = "Port";
	numVisited = 0;
	totalDistance = 0;
	name = "SpaceCraft";

}
// Copy Constructor
SpaceCraft::SpaceCraft(const SpaceCraft & other)
{
	posX = other.posX;
	posY = other.posY;
	direction = other.direction;
	numVisited = other.numVisited;
	totalDistance = other.totalDistance;
	name = other.name;
}
// Destructor
SpaceCraft::~SpaceCraft()
{
}


AsteroidList SpaceCraft::getPreciousAsts() const
{
	return visitedAsts;
}

/* setDirection()
*  sets the direction of the craft
* parameters: string
* return: none */
void SpaceCraft::setDirection(std::string dir) {
	direction = dir;
}

void SpaceCraft::setToVisitCollect(int num, int num1)
{
	toVisit = num;
	toCollect = num1;
}



/* getDirection()
*  gets the direction of the craft
* parameters: none
* return: string                    */
std::string SpaceCraft::getDirection() const
{
	return direction;
}

/* getCollected()
*  gets the number of asteroids collected by the ship
* parameters: none
* return: int                    */
int SpaceCraft::getCollected() const 
{
   return numVisited;
}

/* getTotalDistance()
*  gets the total distance travelled
* parameters: none
* return: double                    */
double SpaceCraft::getTotalDistance() const
{
	return totalDistance;
}

int SpaceCraft::getToVisit() const
{
	return toVisit;
}
int SpaceCraft::getTotalVisited() const
{
	return totalVisited;
}
int SpaceCraft::getTotalCollected() const
{
	return totalCollected;
}
int SpaceCraft::getToCollect() const
{
	return toCollect;
}

/* getClosest()
*  gets the index of the nearest asteroid to the craft
* parameters: double, double, const AsteroidList
* return: int                    */
int SpaceCraft::getClosest(double maxSize, double & distance, const AsteroidList& astList) const
{
	Asteroid closest, next;
	double diffX, diffY, distClosest, distNext;
	bool assumeFirst = false;
	int indexClosest = -1;	// if they've all been collected and user wants
							//more
							// loop through astList and assume the first uncollected asteroid is the
							// closest
	for (int x = 0; x < visitedAsts.getSize() && !assumeFirst; x++)
	{
		// get the asteroid 
		Asteroid current = visitedAsts.getAst(x);
		// check if it's collected
		if (current.getCollected() == false)
		{
			// check if it's not more than maxSize
			if (current.getSize() <= maxSize)
			{
				// assume it is the closest one
				closest = current;
				indexClosest = x;
				assumeFirst = true;
			}
		}
	}
	// calculate distance between the spaceship and the asteroid
	// assumed closest
	diffX = (posX * 10) - (closest.getX() * 10);
	diffY = (posY * 10) - (closest.getY() * 10);
	distClosest = sqrt(pow(diffX, 2) + pow(diffY, 2));

	// search for the closest asteroid
	for (int x = 0; x < visitedAsts.getSize(); x++)
	{
		if (!visitedAsts.getAst(x).getCollected())
		{
			// calculate distance between ship and next asteroid
			diffX = (posX * 10) - (visitedAsts.getAst(x).getX() * 10);
			diffY = (posY * 10) - (visitedAsts.getAst(x).getY() * 10);
			distNext = sqrt(pow(diffX, 2) + pow(diffY, 2));
			//compare the distance with the distance between ship and closest
			if (distClosest > distNext)
			{
				// set closest to the next one if it is closer
				closest = visitedAsts.getAst(x);
				distClosest = distNext;
				indexClosest = x;
			}
		}
	}
	distance = distClosest;
	return indexClosest;


}


/* move()
*  changes the position of the craft and increments the distance travelled
* parameters: int, int, double
* return: none                   */
void SpaceCraft::move(int x, int y, double distance)
{
	setPosition(x, y);
	totalDistance += distance;
}


/* collect()
*  collects an asteroid by setting its status to true (collected)
* parameters: int, AsteroidList
* return: none                    */
void SpaceCraft::collect(int i, AsteroidList & list)
{
	list.setAst(i).setCollected(true);
	// increment member variable
	numVisited++;
	
}

std::string SpaceCraft::to_string()
{
	std::string s = "Asteroids to visit: " + std::to_string(toVisit)
		+ "\nAsteroid Visited: " + std::to_string(totalVisited)
		+ "\nAsteroids to collect: " + std::to_string(toCollect)
		+ "\nAsteroids collected: " + std::to_string(totalCollected)
		+ "\n--------------------------";
	return s;
}

std::string SpaceCraft::getList()
{
	std::string s = "Asteroid" + std::string(5, ' ') + "Position" + std::string(5, ' ')
		+ "Size" + std::string(5, ' ') + "Precious\n"
		+ "--------" + std::string(5, ' ') + "--------" + std::string(5, ' ')
		+ "----"+ std::string(5, ' ') + "-------\n" + visitedAsts.to_string();
	return s;
}
