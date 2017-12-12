// header file for the asteroid class

#ifndef ASTEROID_H
#define ASTEROID_H

#include "Position.h"

class Asteroid
{
public:
	Asteroid();
	Asteroid(int, int, double);
	Asteroid(const Asteroid & other);
	~Asteroid();

	void setStatus(bool);

	bool getStatus() const;
	//Position* getPosition() const;
	int getX() const;
	int getY() const;
	double getSize() const;

private:
	//Position* pos;
	int posX;
	int posY;
	double size;
	bool status;

};


#endif /* ASTEROID_H */

