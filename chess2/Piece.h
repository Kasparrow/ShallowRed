#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include<iostream>
#include<vector>

class Board;

class Piece {
public:
	Piece();
	Piece(int l, int c, Board *b, char co, double v);
	virtual ~Piece() = 0;
	virtual char getName() = 0;
	char getColor();
	int getCoordinate();
	virtual void calculateAuthorizedMoves() = 0;
	void printAuthorizedMoves();
	void setCoordinate(int l, int c);
	bool isAuthorizedMove(int m);
	void setPined(bool p) {
		isPined = p;
	}
protected:
	int x;
	int y;
	bool isPined;
	char color;
	double value;
	Board *board;
	std::vector<int> authorizedMoves;
};

class King : public Piece {
public:
	King();
	King(int l, int c, Board *b, char co, double v);
	~King() {};
	bool hasMoved();
	bool isCheck();
	void KCastling();
	void QCastling();
	char getName();
	void setMoved(bool m);
	void calculateAuthorizedMoves();

private:
	bool moved;
};

class Queen : public Piece {
public:
	Queen();
	Queen(int l, int c, Board *b, char co, double v);
	~Queen() {};
	char getName();
	void calculateAuthorizedMoves();

private:
};

class Rook : public Piece {
public:
	Rook();
	Rook(int l, int c, Board *b, char co, double v);
	~Rook() {};
	bool hasMoved();
	char getName();
	void setMoved(bool m);
	void calculateAuthorizedMoves();

private:
	bool moved; /*! Boolean set to true if the Rook has moved during the game */
};

class Knight : public Piece {
public:
	Knight();
	Knight(int l, int c, Board *b, char co, double v);
	~Knight() {};
	char getName();
	void calculateAuthorizedMoves();

private:
};

class Bishop : public Piece {
public:
	Bishop();
	Bishop(int l, int c, Board *b, char co, double v);
	~Bishop() {};
	char getName();
	void calculateAuthorizedMoves();

private:
};

class Pawn : public Piece {
public:
	Pawn();
	Pawn(int l, int c, Board *b, char co, double v);
	~Pawn() {};
	char getName();
	void calculateAuthorizedMoves();

private:
};

#endif