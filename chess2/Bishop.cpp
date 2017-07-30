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

void Bishop::compute_authorized_moves() {
	authorized_moves.clear();

	//Move top Right
	for (int i = 1; (line + i < 8) && (column + i <8); i++) {
		if (!(board->get_case(line + i, column + i))->is_occupied()) {
			authorized_moves.push_back((line + i) * 8 + column + i);
			board->get_case((line + i), (column + i))->add_threat(this);
		}

		else {
			if (((board->get_case(line + i, column + i)->get_occupant())->get_color() != color)) {
				authorized_moves.push_back((line + i) * 8 + column + i);
				board->get_case((line + i), (column + i))->add_threat(this);
			}
			break;
		}
	}

	//Move top left
	for (int i = 1; (line + i < 8) && (column - i >= 0); i++) {
		if (!(board->get_case(line + i, column - i))->is_occupied()) {
			authorized_moves.push_back((line + i) * 8 + (column - i));
			board->get_case((line + i), (column - i))->add_threat(this);
		}

		else {
			if (((board->get_case(line + i, column - i)->get_occupant())->get_color() != color)) {
				authorized_moves.push_back((line + i) * 8 + (column - i));
				board->get_case((line + i), (column - i))->add_threat(this);
			}
			break;
		}
	}

	//Move back right
	for (int i = 1; (line - i >= 0) && (column + i < 8); i++) {
		if (!(board->get_case(line - i, column + i))->is_occupied()) {
			authorized_moves.push_back((line - i) * 8 + (column + i));
			board->get_case((line - i), (column + i))->add_threat(this);
		}

		else {
			if (((board->get_case(line - i, column + i)->get_occupant())->get_color() != color)) {
				authorized_moves.push_back((line - i) * 8 + (column + i));
				board->get_case((line - i), (column + i))->add_threat(this);
			}
			break;
		}
	}

	//Move back left
	for (int i = 1; (line - i >= 0) && (column - i >= 0); i++) {
		if (!(board->get_case(line - i, column - i))->is_occupied()) {
			authorized_moves.push_back((line - i) * 8 + (column - i));
			board->get_case((line - i), (column - i))->add_threat(this);
		}

		else {
			if (((board->get_case(line - i, column - i)->get_occupant())->get_color() != color)) {
				authorized_moves.push_back((line - i) * 8 + (column - i));
				board->get_case((line - i), (column - i))->add_threat(this);
			}
			break;
		}
	}


}