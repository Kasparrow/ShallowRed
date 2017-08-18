#include "Piece.h"
#include "Board.h"

Knight::Knight() : Piece() { }

Knight::Knight(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) { }

char Knight::get_name() 
{
	if (_color == 'b')
		return 'N';
	else
		return 'n';
}

void Knight::compute_authorized_moves() 
{
	_authorized_moves.clear();

	if (!is_pinned())
		add_knight_moves();
}