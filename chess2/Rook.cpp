#include "Piece.h"
#include "Board.h"

using namespace std;

Rook::Rook() : Piece() { }

Rook::Rook(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {}

char Rook::get_name() 
{
	if (color == 'b')
		return 'R';
	else
		return 'r';
}

bool Rook::has_moved() 
{
	return moved;
}

void Rook::set_moved(bool m) 
{
	moved = m;
}

void Rook::compute_authorized_moves() 
{
	authorized_moves.clear();

	add_top_line_moves(8);
	add_right_line_moves(8);
	add_left_line_moves(8);
	add_bottom_line_moves(8);
}