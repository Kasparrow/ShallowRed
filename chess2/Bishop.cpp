#include "Piece.h"
#include "Board.h"

Bishop::Bishop() : Piece() {

}

Bishop::Bishop(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {

}

char Bishop::get_name() {
	if (color == 'b')
		return 'B';
	else
		return 'b';
}

void Bishop::compute_authorized_moves()
{
	authorized_moves.clear();

	add_top_left_diagonal_moves(8);
	add_top_right_diagonal_moves(8);
	add_bottom_right_diagonal_moves(8);
	add_bottom_left_diagonal_moves(8);
}