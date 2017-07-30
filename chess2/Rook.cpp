#include "Piece.h"
#include "Board.h"

using namespace std;

Rook::Rook() : Piece() {

}

Rook::Rook(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {

}

char Rook::getName() {
	if (color == 'b')
		return 'R';
	else
		return 'r';
}

bool Rook::hasMoved() {
	return moved;
}

void Rook::setMoved(bool m) {
	moved = m;
}

void Rook::calculateAuthorizedMoves() {
	authorizedMoves.clear();

	//Move Toward
	for (int i = 1; x + i < 8; i++) {
		if (!(board->getCase(x + i, y))->isOccupied()) {
			authorizedMoves.push_back((x + i) * 8 + y);
			board->getCase((x + i), y)->addThreat(this);
		}

		else {
			if (((board->getCase(x + i, y)->getOccupant())->getColor() != color)) {
				authorizedMoves.push_back((x + i) * 8 + y);
				board->getCase((x + i), y)->addThreat(this);
			}
			break;
		}
	}

	//Move right
	for (int i = 1; y + i < 8; i++) {
		if (!(board->getCase(x, y + i))->isOccupied()) {
			authorizedMoves.push_back(x * 8 + y + i);
			board->getCase(x, (y + i))->addThreat(this);
		}

		else {
			if (((board->getCase(x, y + i)->getOccupant())->getColor() != color)) {
				authorizedMoves.push_back(x * 8 + y + i);
				board->getCase(x, (y + i))->addThreat(this);
			}
			break;
		}
	}

	//Move back
	for (int i = 1; x - i >= 0; i++) {
		if (!(board->getCase(x - i, y))->isOccupied()) {
			authorizedMoves.push_back((x - i) * 8 + y);
			board->getCase((x - i), y)->addThreat(this);
		}

		else {
			if (((board->getCase(x - i, y)->getOccupant())->getColor() != color)) {
				authorizedMoves.push_back((x - i) * 8 + y);
				board->getCase((x - i), y)->addThreat(this);
			}
			break;
		}
	}

	//Move left
	for (int i = 1; y - i >= 0; i++) {
		if (!(board->getCase(x, y - i))->isOccupied()) {
			authorizedMoves.push_back(x * 8 + y - i);
			board->getCase(x, (y - i))->addThreat(this);
		}

		else {
			if (((board->getCase(x, y - i)->getOccupant())->getColor() != color)) {
				authorizedMoves.push_back(x * 8 + y - i);
				board->getCase(x, (y - i))->addThreat(this);
			}
			break;
		}
	}

}