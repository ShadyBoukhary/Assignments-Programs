// Shady Boukhary
#ifndef ASTEROID_H
#define ASTEROID_H
#include "SpaceObject.h"

class Asteroid:
		public SpaceObject
{
public:
	Asteroid();
	Asteroid(int, int, double, bool);
	Asteroid(const Asteroid & other);
	~Asteroid();

	void setCollected(bool);
	void setVisited(bool);

	bool getCollected() const;
	bool getVisited() const;
	bool getPrecious() const;
	double getSize() const;
	std::string to_string();
	void operator = (const Asteroid&);

private:

	double size;
	bool collected, visited, precious;

};


#endif /* ASTEROID_H */

