#include "Piece.h"
#include "Board.h"

King::King() : Piece() {

}

King::King(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {
	moved = false;
}

void King::set_moved(bool m) {
	moved = m;
}

bool King::has_moved() {
	return moved;
}

bool King::is_check() {
	if (get_color() == 'b')
		return board->get_case(line, column)->is_threatened_by_white();
	else
		return board->get_case(line, column)->is_threatened_by_black();
}

char King::get_name() {
	if (color == 'b')
		return 'K';
	else
		return 'k';
}

void King::compute_authorized_moves() {
	authorized_moves.clear();

	for (int i = -1; i<2; i++) {
		if (line + i >= 0 && line + i < 8) {
			for (int j = -1; j<2; j++) {
				if (column + j >= 0 && column + j < 8 && !(i == 0 && j == 0)) {
					if (!(board->get_case(line + i, column + j))->is_occupied()) {
						authorized_moves.push_back((line + i) * 8 + (column + j));
						board->get_case((line + i), (column + j))->add_threat(this);
					}
					else {
						if (((board->get_case(line + i, column + j))->get_occupant())->get_color() != color) {
							authorized_moves.push_back((line + i) * 8 + (column + j));
							board->get_case((line + i), (column + j))->add_threat(this);
						}
					}
				}
			}
		}
	}
}