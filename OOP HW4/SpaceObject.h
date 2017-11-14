// Shady Boukhary
#pragma once
#include <string>
class SpaceObject
{
public:
	void setPosition(int, int);
	int getX() const;
	int getY() const;
	std::string getName();
	virtual std::string to_string() = 0;

protected:
	int posX, posY;
	std::string name;
};

