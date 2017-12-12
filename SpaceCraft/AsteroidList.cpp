// implementation file for the AsteroidList class

#include "AsteroidList.h"
#include <iostream>
#include <sstream>
#include <iomanip>

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
	if (!isFull())
	{
		list[size] = ast;
		size++;
	}
	else
		std::cout << "\n ERROR: CANNOT ADD TO A FULL LIST\n";
}

/* isFull()
* checks if the array is full
* parameters: none
* return: bool		*/
bool AsteroidList::isFull()
{
	if (size == MAX)
		return true;
	else
		return false;
}

/* isEmpty()
* checks if the array is empty
* parameters: none
* return: bool		*/
bool AsteroidList::isEmpty()
{
	if (size == 0)
		return true;
	else
		return false;
}

/* getSize()
* gets the size of the array (number of asteroids in it)
* parameters: none
* return: int								*/
int AsteroidList::getSize() const
{
	return size;
}

/* setAst()
* gets an asteroid from the array
* parameters: int
* return: Asteroid					 */
Asteroid& AsteroidList::setAst(int i)
{
	return list[i];
}

Asteroid AsteroidList::getAst(int i) const
{
	return list[i];
}

std::string AsteroidList::to_string()
{
	std::ostringstream s;
	for (int x = 0; x < size; x++)
	{
		s << std::setw(4) << x << list[x].to_string();
	}

	s << std::endl << std::endl;
	return s.str();

}
