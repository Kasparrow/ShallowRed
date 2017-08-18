#include "Piece.h"
#include "Functions.h"
#include "Board.h"

using namespace std;

Piece::Piece() : _authorized_moves()
{
	_line = 0;
	_column = 0;
	_is_pinned = false;
	_color = 'w';
	_value = '0';
	_board = 0;
	_pinned_by = 0;
}

Piece::Piece(int l, int c, Board *b, char co, double v) : _authorized_moves() 
{
	_line = l;
	_column = c;
	_is_pinned = false;
	_color = co;
	_value = v;
	_board = b;
	_pinned_by = 0;
}

Piece::~Piece() 
{

}

char Piece::get_color() 
{
	return _color;
}

int Piece::get_coordinates() 
{
	return _line * 8 + _column;
}
void Piece::print_authorized_moves() 
{
	vector<int>::iterator it;

	for (it = _authorized_moves.begin(); it != _authorized_moves.end(); it++)
		cout << col_int_to_char(_column + 1) << _line + 1 << "->" << col_int_to_char((*it % 8) + 1) << (*it / 8) + 1 << ", ";
}

void Piece::set_coordinates(int l, int c) 
{
	_line = l;
	_column = c;
}

bool Piece::is_authorized_move(int m) 
{
	return find(_authorized_moves.begin(), _authorized_moves.end(), m) != _authorized_moves.end();
}

void Piece::add_authorized_move(int line, int column, int case_number)
{
	_authorized_moves.push_back(case_number);
	_board->get_case(line, column)->add_threat(this);
}

bool Piece::check_and_add_authorized_move(int line, int column, int case_number)
{
	bool continue_exploration = true;

	if (!_board->is_case_occupied(line, column))
		add_authorized_move(line, column, case_number);

	else
	{
		if (_board->is_case_occupied_by_opponant(line, column, get_color()))
			add_authorized_move(line, column, case_number);

		continue_exploration = false;
	}

	return continue_exploration;
}

void Piece::add_top_left_diagonal_moves(int distance)
{
	int tmp_line = 0,
		tmp_col = 0,
		tmp_case = 0;

	for (int i = 1; (_line + i < 8) && (_column - i >= 0) && i <= distance; i++) 
	{
		tmp_line = _line + i;
		tmp_col = _column - i;
		tmp_case = (tmp_line * 8) + tmp_col;

		if (!check_and_add_authorized_move(tmp_line, tmp_col, tmp_case))
			break;
	}
}

void Piece::add_top_right_diagonal_moves(int distance)
{
	int tmp_line = 0,
		tmp_col = 0,
		tmp_case = 0;

	for (int i = 1; (_line + i < 8) && (_column + i <8) && i <= distance; i++) 
	{
		tmp_line = _line + i;
		tmp_col = _column + i;
		tmp_case = (tmp_line * 8) + tmp_col;

		if (!check_and_add_authorized_move(tmp_line, tmp_col, tmp_case))
			break;
	}
}

void Piece::add_bottom_left_diagonal_moves(int distance)
{
	int tmp_line = 0,
		tmp_col = 0,
		tmp_case = 0;

	for (int i = 1; (_line - i >= 0) && (_column - i >= 0) && i <= distance; i++)  
	{
		tmp_line = _line - i;
		tmp_col = _column - i;
		tmp_case = (tmp_line * 8) + tmp_col;

		if (!check_and_add_authorized_move(tmp_line, tmp_col, tmp_case))
			break;
	}
}

void Piece::add_bottom_right_diagonal_moves(int distance)
{
	int tmp_line = 0,
		tmp_col = 0,
		tmp_case = 0;

	for (int i = 1; (_line - i >= 0) && (_column + i < 8) && i <= distance; i++) 
	{
		tmp_line = _line - i;
		tmp_col = _column + i;
		tmp_case = (tmp_line * 8) + tmp_col;

		if (!check_and_add_authorized_move(tmp_line, tmp_col, tmp_case))
			break;
	}
}

void Piece::add_top_line_moves(int distance)
{
	int tmp_line = 0,
		tmp_case = 0;

	for (int i = 1; (_line + i) < 8 && i <= distance; i++) 
	{
		tmp_line = _line + i;
		tmp_case = (tmp_line * 8) + _column;

		if (!check_and_add_authorized_move(tmp_line, _column, tmp_case))
			break;
	}
}

void Piece::add_right_line_moves(int distance)
{
	int tmp_col = 0,
		tmp_case = 0;

	for (int i = 1; (_column + i) < 8 && i <= distance; i++)
	{
		tmp_col = _column + i;
		tmp_case = (_line * 8) + tmp_col;
		
		if (!check_and_add_authorized_move(_line, tmp_col, tmp_case))
			break;
	}
}

void Piece::add_left_line_moves(int distance)
{
	int tmp_col = 0,
		tmp_case = 0;

	for (int i = 1; (_column - i) >= 0 && i <= distance; i++) 
	{
		tmp_col = _column - i;
		tmp_case = (_line * 8) + tmp_col;
		
		if (!check_and_add_authorized_move(_line, tmp_col, tmp_case))
			break;
	}
}

void Piece::add_bottom_line_moves(int distance)
{
	int tmp_line = 0,
		tmp_case = 0;
	for (int i = 1; (_line - i) >= 0 && i <= distance; i++) 
	{
		tmp_line = _line - i;
		tmp_case = (tmp_line * 8) + _column;

		if (!check_and_add_authorized_move(tmp_line, _column, tmp_case))
			break;
	}
}

void Piece::add_knight_moves()
{
	for (int i = -2; i < 3; i++)
	{
		// - le cavalier ne se déplace pas en ligne
		if (i == 0)
			continue;

		for (int j = -2; j < 3; j++)
		{
			// - le cavalier ne se déplace pas en colonne et la somme (nouvelle colonne + nouvelle ligne) n'est jamais paire
			if (j == 0 || (i + j) % 2 == 0)
				continue;

			// - limite les déplacements dans l'échiquier
			if ((_line + i) < 0 || (_line + i) > 7 || (_column + j) < 0 || (_column + j) > 7)
				continue;

			// - vérifie que la case n'est pas occupée par une pièce de la même couleur
			if (!_board->is_case_occupied(_line + i, _column + j) || _board->is_case_occupied_by_opponant(_line + i, _column + j, get_color())) 
			{
				_authorized_moves.push_back((_line + i) * 8 + (_column + j));
				_board->get_case((_line + i), (_column + j))->add_threat(this);
			}
		}
	}
}

void Piece::add_white_pawn_forward_moves()
{
	if (_line + 1 < 8 && !(_board->get_case(_line + 1, _column))->is_occupied()) 
	{
		_authorized_moves.push_back((_line + 1) * 8 + _column);
		if (_line == 1 && !(_board->get_case(_line + 2, _column))->is_occupied())
			_authorized_moves.push_back((_line + 2) * 8 + _column);
	}
}

void Piece::add_white_pawn_take_right_moves()
{
	if ((_line + 1 < 8 && _column + 1 <8) && _board->get_case(_line + 1, _column + 1)->is_occupied() && ((_board->get_case(_line + 1, _column + 1))->get_occupant())->get_color() != 'w') 
	{
		_authorized_moves.push_back((_line + 1) * 8 + (_column + 1));
		_board->get_case((_line + 1), (_column + 1))->add_threat(this);
	}
}

void Piece::add_white_pawn_take_left_moves()
{
	if ((_line + 1 < 8 && _column - 1 >= 0) && _board->get_case(_line + 1, _column - 1)->is_occupied() && ((_board->get_case(_line + 1, _column - 1))->get_occupant())->get_color() != 'w') 
	{
		_authorized_moves.push_back((_line + 1) * 8 + (_column - 1));
		_board->get_case((_line + 1), (_column - 1))->add_threat(this);
	}
}

void Piece::add_black_pawn_forward_moves()
{
	if (_line - 1 >= 0 && !(_board->get_case(_line - 1, _column))->is_occupied())
	{
		_authorized_moves.push_back((_line - 1) * 8 + _column);
		if (_line == 6 && !(_board->get_case(_line - 2, _column))->is_occupied())
			_authorized_moves.push_back((_line - 2) * 8 + _column);
	}
}

void Piece::add_black_pawn_take_right_moves()
{
	if ((_line - 1 >= 0 && _column + 1 < 8) && _board->get_case(_line - 1, _column + 1)->is_occupied() && ((_board->get_case(_line - 1, _column + 1))->get_occupant())->get_color() != 'b') {
		_authorized_moves.push_back((_line - 1) * 8 + (_column + 1));
		_board->get_case((_line - 1), (_column + 1))->add_threat(this);
	}
}

void Piece::add_black_pawn_take_left_moves()
{
	if ((_line - 1 >= 0 && _column - 1 >= 0) && _board->get_case(_line - 1, _column - 1)->is_occupied() && ((_board->get_case(_line - 1, _column - 1))->get_occupant())->get_color() != 'b')
	{
		_authorized_moves.push_back((_line - 1) * 8 + (_column - 1));
		_board->get_case((_line - 1), (_column - 1))->add_threat(this);
	}
}

void Piece::set_pinned(bool p)
{
	if (!p)
		_pinned_by = 0;
	
	_is_pinned = p;
}

bool Piece::is_pinned()
{
	return _is_pinned;
}