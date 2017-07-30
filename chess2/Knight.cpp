#include "Piece.h"
#include "Board.h"

Knight::Knight() : Piece() {

}

Knight::Knight(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {

}

char Knight::getName() {
	if (color == 'b')
		return 'N';
	else
		return 'n';
}

void Knight::calculateAuthorizedMoves() {
	authorizedMoves.clear();
	for (int i = -2; i<3; i++) {
		if (i != 0) {
			for (int j = -2; j<3; j++) {
				if (j != 0 && (i + j) % 2 != 0) {
					if ((x + i) >= 0 && (x + i) <= 7 && (y + j) >= 0 && (y + j) <= 7) {
						if (!board->getCase(x + i, y + j)->isOccupied() || (board->getCase(x + i, y + j)->isOccupied() && ((board->getCase(x + i, y + j))->getOccupant())->getColor() != color)) {
							authorizedMoves.push_back((x + i) * 8 + (y + j));
							board->getCase((x + i), (y + j))->addThreat(this);
						}
					}
				}
			}
		}
	}
}