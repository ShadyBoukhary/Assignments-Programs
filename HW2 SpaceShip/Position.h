/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Position.h
 * Author: shady
 *
 * Created on October 1, 2017, 3:15 PM
 */

#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
	Position();
	Position(int, int);
	~Position();

	void setpos(int, int);
	int getX() const;
	int getY() const;

private:
	int posX;
	int posY;
};


#endif /* POSITION_H */

