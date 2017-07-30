#include "Piece.h"
#include "Board.h"

Knight::Knight() : Piece() {

}

Knight::Knight(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {

}

char Knight::get_name() {
	if (color == 'b')
		return 'N';
	else
		return 'n';
}

void Knight::compute_authorized_moves() {
	authorized_moves.clear();
	for (int i = -2; i<3; i++) {
		if (i != 0) {
			for (int j = -2; j<3; j++) {
				if (j != 0 && (i + j) % 2 != 0) {
					if ((line + i) >= 0 && (line + i) <= 7 && (column + j) >= 0 && (column + j) <= 7) {
						if (!board->get_case(line + i, column + j)->is_occupied() || (board->get_case(line + i, column + j)->is_occupied() && ((board->get_case(line + i, column + j))->get_occupant())->get_color() != color)) {
							authorized_moves.push_back((line + i) * 8 + (column + j));
							board->get_case((line + i), (column + j))->add_threat(this);
						}
					}
				}
			}
		}
	}
}