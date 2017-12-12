

#include "SpaceShip.h"
#include <cmath>
#include <random>
#include <ctime>
/* Default Constructor*/
SpaceShip::SpaceShip()
{
	posX = 0;
	posY = 0;
    direction = "Port";
    numCollected = 0;
    totalDistance = 0;
    totalSize = 0;
}

/* Parameterized Constructor*/
SpaceShip::SpaceShip(int x, int y) 
{
	posX = x;
	posY = y;
    direction = "Port";
    numCollected = 0;
    totalDistance = 0;
    totalSize = 0;
}

/* Copy Constructor*/
SpaceShip::SpaceShip(const SpaceShip & other) 
{
    posX = other.posX;
	posY = other.posY;
    direction = other.direction;
    numCollected = other.numCollected;
    totalDistance = other.totalDistance;
    totalSize = other.totalSize;
}

/* Destructor*/
SpaceShip::~SpaceShip() 
{
}

/* setDirection()
 *  sets the direction of the ship
 * parameters: string
 * return: none                     */
void SpaceShip::setDirection(std::string dir) {
    direction = dir;
}

/* setDPosition()
*  sets the position of the ship
* parameters: int, int
* return: none                     */
void SpaceShip::setPosition(int x, int y)  
{
	posX = x;
	posY = y;
}


/* getX()
*  gets the X coordinate of the ship
* parameters: none
* return: int                    */
int SpaceShip::getX() const
{
	return posX;
}

/* getX()
*  gets the X coordinate of the ship
* parameters: none
* return: int                    */
int SpaceShip::getY() const
{
	return posY;
}

/* getY()
*  gets the Y coordinate of the ship
* parameters: none
* return: int                    */
std::string SpaceShip::getDirection() const 
{
    return direction;
}

/* getCollected()
*  gets the number of asteroids collected by the ship
* parameters: none
* return: int                    */
int SpaceShip::getCollected() const 
{
    return numCollected;
}

/* getTotalDistance()
*  gets the total distance travelled
* parameters: none
* return: double                    */
double SpaceShip::getTotalDistance() const
{
    return totalDistance;
}

/* getClosest()
*  gets the index of the nearest asteroid to the ship
* parameters: double, double, const AsteroidList
* return: int                    */
int SpaceShip::getClosest(double maxSize, double & distance, const AsteroidList& astList) const
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
        if (current.getStatus() == false)
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
        if (!astList.getAst(x).getStatus())
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

/* getTotalSize()
*  gets the total size of asteroids collected
* parameters: none
* return: none                    */
double SpaceShip::getTotalSize() const
{
    return totalSize;
}

/* move()
*  changes the position of the ship and increments the distance travelled
* parameters: int, int, double
* return: none                   */
void SpaceShip::move(int x, int y, double distance)
{
    setPosition(x, y);
    totalDistance += distance;
}

/* collect()
*  collects an asteroid by setting its status to true (collected)
* parameters: int, AsteroidList
* return: none                    */
void SpaceShip::collect(int i, AsteroidList & list) 
{
    double size = list.getAst(i).getSize();
    list.getAst(i).setStatus(true);
    // increment member variables
    numCollected++;
    totalSize += size;
    
    
}

/* blast()
*  blasts an asteroid to 2-3 pieces of random sizes
*  equal to the original and random positions
* parameters: int, AsteroidList
* return: none                    */
void SpaceShip::blast(int i, AsteroidList& list)
{
	int randomNum = 0, randomSize = 0;
	double size = list.getAst(i).getSize();
	double total = 0, size1 = 0, size2 = 0, size3 = 0;
	int posX1 = 0, 
		posX2 = 0, posY1 = 0, posY2 = 0, posX3, posY3 = 0;
	// set asteroid status to true
	list.getAst(i).setStatus(true);
	// use a different seed every time

	// diversify the seed since rand() is a terrible generator
	int seed = (int)time(0) + rand();
	srand(seed);
	// generate random number of asteroids
	randomNum = rand() % 3 + 1;
	// generate random positions
	posY1 = rand() % 100;
	posY2 = rand() % 100;
	posX1 = rand() % 100;
	posX3 = rand() % 100;
	posY3 = rand() % 100;
	posX2 = rand() % 100;
	
	


	// to generate a random double using a c++11 way
	// stackoverflow.com
	std::random_device rd;
	std::default_random_engine generator(rd()); // rd() provides a random seed
	std::uniform_real_distribution<double> distribution(1, size);


	// if blasted into 2 asteroids
	if (randomNum == 2)
	{
		// generate random sizes with total equal to original
		while (total != size)
		{
			size1 = distribution(generator);
			size2 = distribution(generator);
		

			// truncate doubles after 2 decimal points
			// because the loop will never find sizes
			// that equal the original otherwise
			// since it will take a very long time
			size1 = size1 * 100;
			size1 = (int)size1;
			size1 = (double)size1;
			size1 /= 100;

			size2 = size2 * 100;
			size2 = (int)size2;
			size2 = (double)size2;
			size2 /= 100;

			total = size1 + size2;
		} 
		// if any asteroid hits the spaceship
		if ((posX2 == posX && posY2 == posY) || (posX1 == posX && posY1 == posY))
		{
			// delay 5 seconds as the ship halts to repair
			system("timeout 5 >nul");
		}
	}
	// if blasted into 3 asteroids
	else
	{		
		// generate random sizes with total equal to original
		while (total != size)
		{
			size1 = distribution(generator);
			size2 = distribution(generator);
			size3 = distribution(generator);

			size1 = size1 * 100;
			size1 = (int)size1;
			size1 = (double)size1;
			size1 /= 100;

			size2 = size2 * 100;
			size2 = (int)size2;
			size2 = (double)size2;
			size2 /= 100;

			size3 = size3 * 100;
			size3 = (int)size3;
			size3 = (double)size3;
			size3 /= 100;

			total = size1 + size2 + size3;
		}
		// create the 3rd asteroid and insert
		Asteroid ast3(posX3, posY3, size3);
		list.insert(ast3);
			// if any asteroid hits the spaceship
		if ((posX3 == posX && posY3 == posY) || (posX2 == posX && posY2 == posY) || (posX1 == posX && posY1 == posY))
		{
			// delay 5 seconds as the ship halts to repair
			system("timeout 5 >nul");
		}
	}
	// create the first 2 and insert them
	Asteroid ast1(posX1, posY1, size1);
	Asteroid ast2(posX2, posY2, size2);
	list.insert(ast1);
	list.insert(ast2);
}
