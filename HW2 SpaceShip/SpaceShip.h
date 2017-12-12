// header file for the SpaceShip class

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <string>
#include "Position.h"
#include "AsteroidList.h"

class SpaceShip {
public:
    SpaceShip();
    SpaceShip(int, int);
    SpaceShip(const SpaceShip & other);
    ~SpaceShip();
    void setDirection(std::string);
    void setPosition(int, int);
	int getX() const;
	int getY() const;
    std::string getDirection() const;
    int getCollected() const;
    double getTotalDistance() const;
    int getClosest(double, double&, const AsteroidList&) const;
    double getTotalSize() const;
    void move(int, int, double);
    void collect(int, AsteroidList&);
	void blast(int, AsteroidList&);

private:
	int posX, posY;
    std::string direction;
    int numCollected;
    double totalDistance, totalSize;

};

#endif /* SPACESHIP_H */

