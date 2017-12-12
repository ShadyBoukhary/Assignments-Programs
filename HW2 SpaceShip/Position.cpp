
#include "Position.h"
#include<iostream>

Position::Position()
{
	posX = 0;
	posY = 0;
}
Position::Position(int x = 0, int y = 0)
{
	posX = x;
	posY = y;
}


Position::~Position()
{
	std::cout << "destructing\n";
}

void Position::setpos(int x, int y)
{
	posX = x;
	posY = y;
}
int Position::getX() const
{
	return posX;
}

int Position::getY() const
{
	return posY;
}
