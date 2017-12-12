// header file for AsteroidList Class

#ifndef ASTEROIDLIST_H
#define ASTEROIDLIST_H

#include "Asteroid.h"

class AsteroidList
{
public:
	AsteroidList();
	AsteroidList(const AsteroidList & other);
	~AsteroidList();
	void insert(const Asteroid&);

	int getSize() const;
	Asteroid& getAst(int) const;
	

private:
	static const int MAX = 100;
	int size;
	Asteroid *list;
};

#endif /* ASTEROIDLIST_H */

