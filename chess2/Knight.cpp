#include "Piece.h"
#include "Board.h"

Knight::Knight() : Piece() { }

Knight::Knight(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) { }

char Knight::get_name() 
{
	if (color == 'b')
		return 'N';
	else
		return 'n';
}

void Knight::compute_authorized_moves() 
{
	authorized_moves.clear();

	add_knight_moves();
}