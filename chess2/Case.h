#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED

#include <iostream>
#include <list>
#include "Piece.h"

class Board;

class Case {
public:
	Case();
	Case(int l, int c, Board *b, Piece *occupant);
	void print();
	bool isOccupied();
	Piece* getOccupant();
	void setOccupant(Piece* p);
	void addThreat(Piece* p);
	void removeThreat(Piece* p);
	void clearThreats();
	void printThreats();
	bool isThreatenedByBlack();
	bool isThreatenedByWhite();

private:
	int x;
	int y;
	Board* board;
	Piece *occupant;
	std::list<Piece*> threatenedBy;
};

#endif