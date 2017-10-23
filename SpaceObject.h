#pragma once
class SpaceObject
{
public:
	void setPosition(int, int);
	int getX() const;
	int getY() const;

protected:
	int posX, posY;
};

