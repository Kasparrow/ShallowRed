#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <list>
#include <string>
#include "Functions.h"
#include "Piece.h"

class Board;

class Player {
public:
	static const int MOVE = 0;
	static const int OFFER_DRAW = 1;
	static const int ABANDON = 2;
	Player();
	Player(Board *b, char c);
	void addPiece(Piece *p);
	void removePiece(Piece *p);
	void printListPieces();
	void calculateAllAuthorizedMoves();
	void printAllAuthorizedMoves();
	int play();
	char getColor();
	bool checkKCastling();
	bool checkQCastling();
	bool isCheck();
	void KCastling();
	void QCastling();
	std::list<Piece*>& getListPieces();

private:
	std::list<Piece*> pieces;
	Board *board;
	char color;
};

#endif