// header file for the SpaceShip class

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "SpaceCraft.h"


class SpaceShip :
		public SpaceCraft
{
public:
    SpaceShip();
    SpaceShip(int, int);
    SpaceShip(const SpaceShip & other);
    ~SpaceShip();

    double getTotalSize() const;
    virtual void collect(int, AsteroidList&);
	void blast(int, AsteroidList&);

private:
    double totalSize;

};

#endif /* SPACESHIP_H */

