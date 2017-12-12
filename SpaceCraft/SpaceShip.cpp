#include "SpaceShip.h"
#include <cmath>
#include <random>
#include <ctime>
#include <sstream>
#include <iomanip>


/* Default Constructor*/
SpaceShip::SpaceShip()
{
	totalSize = 0;
	name = "SpaceShip";
}

/* Parameterized Constructor*/
SpaceShip::SpaceShip(int x, int y) : SpaceCraft(x, y)
{
	totalSize = 0;
	name = "SpaceShip";
}

/* Copy Constructor*/
SpaceShip::SpaceShip(const SpaceShip & other) : SpaceCraft(other)
{
	totalSize = other.totalSize;
	name = other.name;
}

/* Destructor*/
SpaceShip::~SpaceShip()
{
}



/* getTotalSize()
*  gets the total size of asteroids collected
* parameters: none
* return: none                    */
double SpaceShip::getTotalSize() const
{
	return totalSize;
}



/* collect()
*  collects an asteroid by setting its status to true (collected)
* parameters: int, AsteroidList
* return: none                    */
void SpaceShip::collect(int i)
{
	double size = visitedAsts.getAst(i).getSize();
	visitedAsts.setAst(i).setCollected(true);
	// increment member variables
	numVisited++;
	totalCollected++;
	totalSize += size;
}

/* blast()
*  blasts an asteroid to 2-3 pieces of random sizes
*  equal to the original and random positions
* parameters: int, AsteroidList
* return: none                    */
void SpaceShip::blast(int i)
{
	int randomNum = 0, randomSize = 0;
	double size = visitedAsts.getAst(i).getSize();
	bool prec = visitedAsts.getAst(i).getPrecious();
	double total = 0, size1 = 0, size2 = 0, size3 = 0;
	int posX1 = 0,
		posX2 = 0, posY1 = 0, posY2 = 0, posX3, posY3 = 0;
	// set asteroid status to true
	visitedAsts.setAst(i).setCollected(true);

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
		Asteroid ast3(posX3, posY3, size3, prec);
		visitedAsts.insert(ast3);
		// if any asteroid hits the spaceship
		if ((posX3 == posX && posY3 == posY) || (posX2 == posX && posY2 == posY) || (posX1 == posX && posY1 == posY))
		{
			// delay 5 seconds as the ship halts to repair
			system("timeout 5 >nul");
		}
	}
	// create the first 2 and insert them
	Asteroid ast1(posX1, posY1, size1, prec);
	Asteroid ast2(posX2, posY2, size2, prec);
	visitedAsts.insert(ast1);
	visitedAsts.insert(ast2);
}

// returns a formated string containing member data
std::string SpaceShip::to_string()
{
	std::string pos = "(" + std::to_string(getX()) + ", " + std::to_string(getY()) + ")";
	std::ostringstream s;
	s << getName() << std::setw(12) << pos << std::setw(13) << std::to_string(numVisited)
		<< std::setw(27) << std::fixed << std::setprecision(2) << totalSize << std::endl;

	return s.str();
}
