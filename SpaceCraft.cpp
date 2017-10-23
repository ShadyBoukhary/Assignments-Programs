#include "SpaceCraft.h"



SpaceCraft::SpaceCraft()
{
	posX = 0;
	posY = 0;
	direction = "Port";
	numVisited = 0;
	totalDistance = 0;
}

SpaceCraft::SpaceCraft(int x, int y)
{
	posX = x;
	posY = y;
	direction = "Port";
	numVisited = 0;
	totalDistance = 0;
}

SpaceCraft::SpaceCraft(const SpaceCraft & other)
{
	posX = other.posX;
	posY = other.posY;
	direction = other.direction;
	numVisited = other.numVisited;
	totalDistance = other.totalDistance;
}

SpaceCraft::~SpaceCraft()
{
}


/* setDirection()
*  sets the direction of the craft
* parameters: string
* return: none */
void SpaceCraft::setDirection(std::string dir) {
	direction = dir;
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
	for (int x = 0; x < astList.getSize() && !assumeFirst; x++)
	{
		// get the asteroid 
		Asteroid current = astList.getAst(x);
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
	for (int x = 0; x < astList.getSize(); x++)
	{
		if (!astList.getAst(x).getCollected())
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
