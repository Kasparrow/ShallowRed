#include "Piece.h"
#include "Board.h"

using namespace std;

Pawn::Pawn() : Piece() {}

Pawn::Pawn(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {}

char Pawn::get_name() 
{
	if (color == 'b')
		return 'P';
	else
		return 'p';
}

void Pawn::compute_authorized_moves() 
{
	authorized_moves.clear();

	if (color == 'w')
		add_white_pawn_moves();


	else if (color == 'b')
		add_black_pawn_moves();
} 