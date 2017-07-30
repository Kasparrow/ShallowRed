#include "Piece.h"
#include "Board.h"

using namespace std;

Pawn::Pawn() : Piece() {

}

Pawn::Pawn(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {

}

char Pawn::get_name() {
	if (color == 'b')
		return 'P';
	else
		return 'p';
}

void Pawn::compute_authorized_moves() {

	authorized_moves.clear();

	//White Pawn :
	if (color == 'w') {
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

		//TODO : En passant

	}


	//Black Pawn :
	if (color == 'b') {
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
} 