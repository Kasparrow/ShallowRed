#include "Piece.h"
#include "Board.h"

Queen::Queen() : Piece() {

}

Queen::Queen(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {

}

char Queen::get_name() {
	if (color == 'b')
		return 'Q';
	else
		return 'q';
}

void Queen::compute_authorized_moves() {
	authorized_moves.clear();

	//Move Toward
	for (int i = 1; line + i < 8; i++) {
		if (!(board->get_case(line + i, column))->is_occupied()) {
			authorized_moves.push_back((line + i) * 8 + column);
			board->get_case((line + i), column)->add_threat(this);
		}

		else {
			if (((board->get_case(line + i, column)->get_occupant())->get_color() != color)) {
				authorized_moves.push_back((line + i) * 8 + column);
				board->get_case((line + i), column)->add_threat(this);
			}
			break;
		}
	}

	//Move right
	for (int i = 1; column + i < 8; i++) {
		if (!(board->get_case(line, column + i))->is_occupied()) {
			authorized_moves.push_back(line * 8 + column + i);
			board->get_case(line, (column + i))->add_threat(this);
		}

		else {
			if (((board->get_case(line, column + i)->get_occupant())->get_color() != color)) {
				authorized_moves.push_back(line * 8 + column + i);
				board->get_case(line, column + i)->add_threat(this);
			}
			break;
		}
	}

	//Move back
	for (int i = 1; line - i >= 0; i++) {
		if (!(board->get_case(line - i, column))->is_occupied()) {
			authorized_moves.push_back((line - i) * 8 + column);
			board->get_case((line - i), column)->add_threat(this);
		}

		else {
			if (((board->get_case(line - i, column)->get_occupant())->get_color() != color)) {
				authorized_moves.push_back((line - i) * 8 + column);
				board->get_case((line - i), column)->add_threat(this);
			}
			break;
		}
	}

	//Move left
	for (int i = 1; column - i >= 0; i++) {
		if (!(board->get_case(line, column - i))->is_occupied()) {
			authorized_moves.push_back(line * 8 + column - i);
			board->get_case(line, (column - i))->add_threat(this);
		}

		else {
			if (((board->get_case(line, column - i)->get_occupant())->get_color() != color)) {
				authorized_moves.push_back(line * 8 + column - i);
				board->get_case(line, (column - i))->add_threat(this);
			}
			break;
		}
	}

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