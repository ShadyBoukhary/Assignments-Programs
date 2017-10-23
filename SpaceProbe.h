#pragma once
#include "SpaceCraft.h"
class SpaceProbe :
	public SpaceCraft
{
public:
	SpaceProbe();
	SpaceProbe(int, int);
	SpaceProbe(const SpaceProbe & other);
	~SpaceProbe();
	AsteroidList getPreciousAsts() const;
	virtual void collect(int, AsteroidList&);
	virtual int getClosest(double, double&, const AsteroidList&) const;


private:
	AsteroidList visitedAsts;
};

