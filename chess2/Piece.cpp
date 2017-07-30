#include "Piece.h"
#include "Functions.h"
#include <algorithm>

using namespace std;

Piece::Piece() : authorized_moves() {
	line = 0;
	column = 0;
	is_pined = false;
	color = 'w';
	value = '0';
	board = 0;
}

Piece::Piece(int l, int c, Board *b, char co, double v) : authorized_moves() {
	line = l;
	column = c;
	is_pined = false;
	color = co;
	value = v;
	board = b;
}

Piece::~Piece() {

}

char Piece::get_color() {
	return color;
}

int Piece::get_coordinates() {
	return line * 8 + column;
}
void Piece::print_authorized_moves() {
	vector<int>::iterator it;

	for (it = authorized_moves.begin(); it != authorized_moves.end(); it++)
		cout << col_int_to_char(column + 1) << line + 1 << "->" << col_int_to_char((*it % 8) + 1) << (*it / 8) + 1 << ", ";
}

void Piece::set_coordinates(int l, int c) {
	line = l;
	column = c;
}

bool Piece::is_authorized_move(int m) {
	if (find(authorized_moves.begin(), authorized_moves.end(), m) != authorized_moves.end())
		return true;
	return false;
}