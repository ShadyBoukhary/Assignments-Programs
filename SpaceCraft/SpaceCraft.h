// Shady Boukhary
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
	static void setToVisitCollect(int, int);
	AsteroidList getPreciousAsts() const;
	std::string getDirection() const;
	int getCollected() const;
	double getTotalDistance() const;
	int getToVisit() const;
	int getTotalVisited() const;
	int getTotalCollected() const;
	int getToCollect() const;
	virtual int getClosest(double, double&, const AsteroidList&) const;
	virtual void collect(int, AsteroidList&);
	void move(int, int, double);
	virtual std::string to_string();
	std::string getList();

protected:
	std::string direction;
	double totalDistance;
	int numVisited;
	static int toVisit;
	static int totalVisited;
	static int totalCollected;
	static int toCollect;
	static AsteroidList visitedAsts;

};

