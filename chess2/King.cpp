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

bool King::is_in_check() 
{
	if (get_color() == 'b')
		return _board->get_case(_line, _column)->is_threatened_by_white();
	else
		return _board->get_case(_line, _column)->is_threatened_by_black();
}

char King::get_name() 
{
	if (_color == 'b')
		return 'K';
	else
		return 'k';
}

void King::compute_authorized_moves() 
{
	_authorized_moves.clear();

	add_top_left_diagonal_moves(1);
	add_top_right_diagonal_moves(1);
	add_bottom_left_diagonal_moves(1);
	add_bottom_right_diagonal_moves(1);
	add_top_line_moves(1);
	add_right_line_moves(1);
	add_left_line_moves(1);
	add_bottom_line_moves(1);
}

void King::set_coordinates(int l, int c)
{
	Piece::set_coordinates(l, c);

	if(!has_moved())
		set_moved(true);
}

void King::check_pinned_pieces(int line_modifier, int column_modifier)
{
	char	king_color = get_color(),
			opponent_color = (king_color == 'w') ? 'b' : 'w';
	int		king_coordinates = this->get_coordinates(),
			x_coordinates = (king_coordinates / 8) + line_modifier,
			y_coordinates = (king_coordinates % 8) + column_modifier;
	Piece*	tmp_pined = 0;
	Piece*	tmp_occupant = 0;
	Case*	current_case = 0;

	while ((x_coordinates >= 0 && x_coordinates < 8) && (y_coordinates >= 0 && y_coordinates < 8))
	{
		current_case = _board->get_case(x_coordinates, y_coordinates);

		if (current_case->is_occupied())
		{
			tmp_occupant = current_case->get_occupant();

			if (tmp_occupant->get_color() == king_color && tmp_pined == 0)
				tmp_pined = tmp_occupant;

			else if (tmp_occupant->get_color() != king_color && tmp_pined != 0)
			{ 
				bool pinned_by_queen = (tmp_occupant->get_name() == 'Q' || tmp_occupant->get_name() == 'q'),
					 pinned_by_rook = (tmp_occupant->get_name() == 'R' || tmp_occupant->get_name() == 'r' && (line_modifier == 0 || column_modifier == 0)),
					 pinned_by_bishop = (tmp_occupant->get_name() == 'B' || tmp_occupant->get_name() == 'b' && (line_modifier != 0 && column_modifier != 0));
				
				if (pinned_by_queen || pinned_by_rook || pinned_by_bishop)
					tmp_pined->set_pinned(current_case->get_occupant());

				break;
			}

			else
				break;
		} 

		x_coordinates += line_modifier,
		y_coordinates += column_modifier;
	}
}