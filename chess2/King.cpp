#include "Piece.h"
#include "Board.h"

King::King() : Piece() {}

King::King(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) 
{
	moved = false;
}

void King::set_moved(bool m) 
{
	moved = m;
}

bool King::has_moved() 
{
	return moved;
}

bool King::is_check() 
{
	if (get_color() == 'b')
		return board->get_case(line, column)->is_threatened_by_white();
	else
		return board->get_case(line, column)->is_threatened_by_black();
}

char King::get_name() 
{
	if (color == 'b')
		return 'K';
	else
		return 'k';
}

void King::compute_authorized_moves() 
{
	authorized_moves.clear();

	add_top_left_diagonal_moves(1);
	add_top_right_diagonal_moves(1);
	add_bottom_left_diagonal_moves(1);
	add_bottom_right_diagonal_moves(1);
	add_top_line_moves(1);
	add_right_line_moves(1);
	add_left_line_moves(1);
	add_bottom_line_moves(1);
}