// Shady Boukhary
#ifndef ASTEROIDLIST_H
#define ASTEROIDLIST_H

#include "Asteroid.h"

class AsteroidList
{
public:
	AsteroidList();
	AsteroidList(const AsteroidList & other);
	~AsteroidList();
	bool isFull();
	bool isEmpty();
	void insert(const Asteroid&);
	int getSize() const;
	Asteroid getAst(int) const;

	Asteroid& setAst(int);
	std::string to_string();

private:
	static const int MAX = 100;
	int size;
	Asteroid *list;
};

#endif /* ASTEROIDLIST_H */

