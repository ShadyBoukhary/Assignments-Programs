#pragma once
#include "SpaceObject.h"
#include "AsteroidList.h"
#include <string>

class SpaceCraft :
	public SpaceObject
{
public:
	SpaceCraft();
	SpaceCraft(int, int);
	SpaceCraft(const SpaceCraft & other);
	~SpaceCraft();

	void setDirection(std::string);
	std::string getDirection() const;
	int getCollected() const;
	double getTotalDistance() const;
	virtual int getClosest(double, double&, const AsteroidList&) const;
	virtual void collect(int, AsteroidList&);
	void move(int, int, double);

protected:
	std::string direction;
	double totalDistance;
	int numVisited;
};

