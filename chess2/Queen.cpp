#include "Piece.h"
#include "Board.h"

Queen::Queen() : Piece() {}

Queen::Queen(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {}

char Queen::get_name() 
{
	if (color == 'b')
		return 'Q';
	else
		return 'q';
}

void Queen::compute_authorized_moves() 
{
	authorized_moves.clear();

	add_top_left_diagonal_moves(8);
	add_top_right_diagonal_moves(8);
	add_bottom_left_diagonal_moves(8);
	add_bottom_right_diagonal_moves(8);
	add_top_line_moves(8);
	add_right_line_moves(8);
	add_left_line_moves(8);
	add_bottom_line_moves(8);
}