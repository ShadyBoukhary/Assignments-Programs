// implementation file for the AsteroidList class

#include "AsteroidList.h"

/* Default Constructor*/
AsteroidList::AsteroidList()
{
	size = 0;
	list = new Asteroid[MAX];
}

/* Copy Constructor*/
AsteroidList::AsteroidList(const AsteroidList & other)
{
	size = other.size;
	list = new Asteroid[MAX];
	for (int x = 0; x < size; x++)
		list[x] = other.list[x];
}

/* Destructor*/
AsteroidList::~AsteroidList()
{
	delete[] list;
	list = 0;
}

/* insert()
* inserts an asteroid into the array of asteroids
* parameters: const Asteroid
* return: none								*/
void AsteroidList::insert(const Asteroid& ast)
{
	list[size] = ast;
	size++;
}

/* getSize()
* gets the size of the array (number of asteroids in it)
* parameters: none
* return: int								*/
int AsteroidList::getSize() const
{
	return size;
}

/* getAst()
* gets an asteroid from the array
* parameters: int
* return: Asteroid					 */
Asteroid& AsteroidList::getAst(int i) const
{
	return list[i];
}