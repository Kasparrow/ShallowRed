#include "Piece.h"
#include "Board.h"

King::King() : Piece() {

}

King::King(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {
	moved = false;
}

void King::setMoved(bool m) {
	moved = m;
}

bool King::hasMoved() {
	return moved;
}

bool King::isCheck() {
	if (getColor() == 'b')
		return board->getCase(x, y)->isThreatenedByWhite();
	else
		return board->getCase(x, y)->isThreatenedByBlack();
}

char King::getName() {
	if (color == 'b')
		return 'K';
	else
		return 'k';
}

void King::calculateAuthorizedMoves() {
	authorizedMoves.clear();

	for (int i = -1; i<2; i++) {
		if (x + i >= 0 && x + i < 8) {
			for (int j = -1; j<2; j++) {
				if (y + j >= 0 && y + j < 8 && !(i == 0 && j == 0)) {
					if (!(board->getCase(x + i, y + j))->isOccupied()) {
						authorizedMoves.push_back((x + i) * 8 + (y + j));
						board->getCase((x + i), (y + j))->addThreat(this);
					}
					else {
						if (((board->getCase(x + i, y + j))->getOccupant())->getColor() != color) {
							authorizedMoves.push_back((x + i) * 8 + (y + j));
							board->getCase((x + i), (y + j))->addThreat(this);
						}
					}
				}
			}
		}
	}
}