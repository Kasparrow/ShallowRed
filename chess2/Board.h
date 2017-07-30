#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>
#include <sstream>
#include <exception>
#include <list>
#include <stdio.h>
#include "Player.h"
#include "Case.h"

class Case;
class Player;

class Board {
public:
	static const int BLACK_WIN = 0;
	static const int WHITE_WIN = 1;
	static const int DRAW = 2;

	Board();
	~Board();
	void print();
	Case* getCase(int l, int c);
	int game();
	void calculatePinedPieces();
	void calculateThreatsAndAuthorizedMoves();
	bool move(int x_start, int y_start, int x_end, int y_end, char c);

private:
	Case* arrayCase[64];
	Player white;
	Player black;
};

#endif