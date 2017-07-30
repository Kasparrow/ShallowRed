#include "Piece.h"
#include "Functions.h"
#include <algorithm>

using namespace std;

Piece::Piece() : authorizedMoves() {
	x = 0;
	y = 0;
	isPined = false;
	color = 'w';
	value = '0';
	board = 0;
}

Piece::Piece(int l, int c, Board *b, char co, double v) : authorizedMoves() {
	x = l;
	y = c;
	isPined = false;
	color = co;
	value = v;
	board = b;
}

Piece::~Piece() {

}

char Piece::getColor() {
	return color;
}

int Piece::getCoordinate() {
	return x * 8 + y;
}
void Piece::printAuthorizedMoves() {
	vector<int>::iterator it;

	for (it = authorizedMoves.begin(); it != authorizedMoves.end(); it++)
		cout << col_int_to_char(y + 1) << x + 1 << "->" << col_int_to_char((*it % 8) + 1) << (*it / 8) + 1 << ", ";
}

void Piece::setCoordinate(int l, int c) {
	x = l;
	y = c;
}

bool Piece::isAuthorizedMove(int m) {
	if (find(authorizedMoves.begin(), authorizedMoves.end(), m) != authorizedMoves.end())
		return true;
	return false;
}