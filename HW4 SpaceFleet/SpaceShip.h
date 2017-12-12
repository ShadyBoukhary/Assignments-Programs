// Shady Boukhary
// header file for the SpaceShip class

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "SpaceCraft.h"


class SpaceShip :
		public SpaceCraft
{
public:
	// constructors
    SpaceShip();
    SpaceShip(int, int);
    SpaceShip(const SpaceShip & other);
    ~SpaceShip();

	// getter
    double getTotalSize() const;
	// to collect asteroids
    virtual void collect(int);
	// to blast large ones
	void blast(int);
	std::string to_string();

private:
    double totalSize;

};

#endif /* SPACESHIP_H */

