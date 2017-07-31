#include "Piece.h"
#include "Functions.h"
#include "Board.h"

using namespace std;

Piece::Piece() : authorized_moves()
{
	line = 0;
	column = 0;
	is_pined = false;
	color = 'w';
	value = '0';
	board = 0;
}

Piece::Piece(int l, int c, Board *b, char co, double v) : authorized_moves() 
{
	line = l;
	column = c;
	is_pined = false;
	color = co;
	value = v;
	board = b;
}

Piece::~Piece() 
{

}

char Piece::get_color() 
{
	return color;
}

int Piece::get_coordinates() 
{
	return line * 8 + column;
}
void Piece::print_authorized_moves() 
{
	vector<int>::iterator it;

	for (it = authorized_moves.begin(); it != authorized_moves.end(); it++)
		cout << col_int_to_char(column + 1) << line + 1 << "->" << col_int_to_char((*it % 8) + 1) << (*it / 8) + 1 << ", ";
}

void Piece::set_coordinates(int l, int c) 
{
	line = l;
	column = c;
}

bool Piece::is_authorized_move(int m) 
{
	return find(authorized_moves.begin(), authorized_moves.end(), m) != authorized_moves.end();
}

void Piece::add_top_left_diagonal_moves(int distance)
{
	int tmp_line = 0,
		tmp_col = 0,
		tmp_case = 0;

	for (int i = 1; (line + i < 8) && (column - i >= 0) && i <= distance; i++) 
	{
		tmp_line = line + i;
		tmp_col = column - i;
		tmp_case = (tmp_line * 8) + tmp_col;

		if (!board->is_case_occupied(tmp_line, tmp_col))
		{
			authorized_moves.push_back(tmp_case);
			board->get_case(tmp_line, tmp_col)->add_threat(this);
		}

		else 
		{
			if (board->is_case_occupied_by_opponant(tmp_line, tmp_col, get_color()))
			{
				authorized_moves.push_back(tmp_case);
				board->get_case(tmp_line, tmp_col)->add_threat(this);
			}
			break;
		}
	}
}

void Piece::add_top_right_diagonal_moves(int distance)
{
	int tmp_line = 0,
		tmp_col = 0,
		tmp_case = 0;

	for (int i = 1; (line + i < 8) && (column + i <8) && i <= distance; i++) 
	{
		tmp_line = line + i;
		tmp_col = column + i;
		tmp_case = (tmp_line * 8) + tmp_col;

		if (!(board->get_case(line + i, column + i))->is_occupied()) 
		{
			authorized_moves.push_back((line + i) * 8 + column + i);
			board->get_case((line + i), (column + i))->add_threat(this);
		}

		else 
		{
			if (((board->get_case(line + i, column + i)->get_occupant())->get_color() != color)) 
			{
				authorized_moves.push_back((line + i) * 8 + column + i);
				board->get_case((line + i), (column + i))->add_threat(this);
			}
			break;
		}
	}
}

void Piece::add_bottom_left_diagonal_moves(int distance)
{
	for (int i = 1; (line - i >= 0) && (column - i >= 0) && i <= distance; i++)  
	{
		if (!(board->get_case(line - i, column - i))->is_occupied()) 
		{
			authorized_moves.push_back((line - i) * 8 + (column - i));
			board->get_case((line - i), (column - i))->add_threat(this);
		}

		else 
		{
			if (((board->get_case(line - i, column - i)->get_occupant())->get_color() != color)) 
			{
				authorized_moves.push_back((line - i) * 8 + (column - i));
				board->get_case((line - i), (column - i))->add_threat(this);
			}
			break;
		}
	}
}

void Piece::add_bottom_right_diagonal_moves(int distance)
{
	for (int i = 1; (line - i >= 0) && (column + i < 8) && i <= distance; i++) 
	{
		if (!(board->get_case(line - i, column + i))->is_occupied()) 
		{
			authorized_moves.push_back((line - i) * 8 + (column + i));
			board->get_case((line - i), (column + i))->add_threat(this);
		}

		else 
		{
			if (((board->get_case(line - i, column + i)->get_occupant())->get_color() != color)) 
			{
				authorized_moves.push_back((line - i) * 8 + (column + i));
				board->get_case((line - i), (column + i))->add_threat(this);
			}
			break;
		}
	}
}

void Piece::add_top_line_moves(int distance)
{
	for (int i = 1; (line + i) < 8 && i <= distance; i++) 
	{
		if (!(board->get_case(line + i, column))->is_occupied()) 
		{
			authorized_moves.push_back((line + i) * 8 + column);
			board->get_case((line + i), column)->add_threat(this);
		}

		else 
		{
			if (((board->get_case(line + i, column)->get_occupant())->get_color() != color)) 
			{
				authorized_moves.push_back((line + i) * 8 + column);
				board->get_case((line + i), column)->add_threat(this);
			}
			break;
		}
	}
}

void Piece::add_right_line_moves(int distance)
{
	for (int i = 1; (column + i) < 8 && i <= distance; i++) {
		if (!(board->get_case(line, column + i))->is_occupied()) 
		{
			authorized_moves.push_back(line * 8 + column + i);
			board->get_case(line, (column + i))->add_threat(this);
		}

		else 
		{
			if (((board->get_case(line, column + i)->get_occupant())->get_color() != color)) 
			{
				authorized_moves.push_back(line * 8 + column + i);
				board->get_case(line, (column + i))->add_threat(this);
			}
			break;
		}
	}
}

void Piece::add_left_line_moves(int distance)
{
	for (int i = 1; (column - i) >= 0 && i <= distance; i++) 
	{
		if (!(board->get_case(line, column - i))->is_occupied()) 
		{
			authorized_moves.push_back(line * 8 + column - i);
			board->get_case(line, (column - i))->add_threat(this);
		}

		else 
		{
			if (((board->get_case(line, column - i)->get_occupant())->get_color() != color)) 
			{
				authorized_moves.push_back(line * 8 + column - i);
				board->get_case(line, (column - i))->add_threat(this);
			}
			break;
		}
	}
}

void Piece::add_bottom_line_moves(int distance)
{
	for (int i = 1; (line - i) >= 0 && i <= distance; i++) 
	{
		if (!(board->get_case(line - i, column))->is_occupied()) 
		{
			authorized_moves.push_back((line - i) * 8 + column);
			board->get_case((line - i), column)->add_threat(this);
		}

		else 
		{
			if (((board->get_case(line - i, column)->get_occupant())->get_color() != color)) 
			{
				authorized_moves.push_back((line - i) * 8 + column);
				board->get_case((line - i), column)->add_threat(this);
			}

			break;
		}
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
			if ((line + i) < 0 || (line + i) > 7 || (column + j) < 0 || (column + j) > 7)
				continue;

			// - vérifie que la case n'est pas occupée par une pièce de la même couleur
			if (!board->is_case_occupied(line + i, column + j) || board->is_case_occupied_by_opponant(line + i, column + j, get_color())) 
			{
				authorized_moves.push_back((line + i) * 8 + (column + j));
				board->get_case((line + i), (column + j))->add_threat(this);
			}
		}
	}
}

void Piece::add_white_pawn_moves()
{
	//Move forward
	if (line + 1 < 8 && !(board->get_case(line + 1, column))->is_occupied()) {
		authorized_moves.push_back((line + 1) * 8 + column);
		if (line == 1 && !(board->get_case(line + 2, column))->is_occupied())
			authorized_moves.push_back((line + 2) * 8 + column);
	}

	//Take
	if ((line + 1 < 8 && column - 1 >= 0) && board->get_case(line + 1, column - 1)->is_occupied() && ((board->get_case(line + 1, column - 1))->get_occupant())->get_color() != 'w') {
		authorized_moves.push_back((line + 1) * 8 + (column - 1));
		board->get_case((line + 1), (column - 1))->add_threat(this);
	}

	if ((line + 1 < 8 && column + 1 <8) && board->get_case(line + 1, column + 1)->is_occupied() && ((board->get_case(line + 1, column + 1))->get_occupant())->get_color() != 'w') {
		authorized_moves.push_back((line + 1) * 8 + (column + 1));
		board->get_case((line + 1), (column + 1))->add_threat(this);
	}
}

void Piece::add_black_pawn_moves()
{
	//Move forward
	if (line - 1 >= 0 && !(board->get_case(line - 1, column))->is_occupied()) {
		authorized_moves.push_back((line - 1) * 8 + column);
		if (line == 6 && !(board->get_case(line - 2, column))->is_occupied())
			authorized_moves.push_back((line - 2) * 8 + column);
	}

	//Take
	if ((line - 1 >= 0 && column - 1 >= 0) && board->get_case(line - 1, column - 1)->is_occupied() && ((board->get_case(line - 1, column - 1))->get_occupant())->get_color() != 'b') {
		authorized_moves.push_back((line - 1) * 8 + (column - 1));
		board->get_case((line - 1), (column - 1))->add_threat(this);
	}

	if ((line - 1 >= 0 && column + 1 < 8) && board->get_case(line - 1, column + 1)->is_occupied() && ((board->get_case(line - 1, column + 1))->get_occupant())->get_color() != 'b') {
		authorized_moves.push_back((line - 1) * 8 + (column + 1));
		board->get_case((line - 1), (column + 1))->add_threat(this);
	}

	//TODO : En passant
}