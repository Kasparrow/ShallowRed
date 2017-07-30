#include "Piece.h"
#include "Board.h"

Bishop::Bishop() : Piece() {

}

Bishop::Bishop(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {

}

char Bishop::getName() {
	if (color == 'b')
		return 'B';
	else
		return 'b';
}

void Bishop::calculateAuthorizedMoves() {
	authorizedMoves.clear();

	//Move top Right
	for (int i = 1; (x + i < 8) && (y + i <8); i++) {
		if (!(board->getCase(x + i, y + i))->isOccupied()) {
			authorizedMoves.push_back((x + i) * 8 + y + i);
			board->getCase((x + i), (y + i))->addThreat(this);
		}

		else {
			if (((board->getCase(x + i, y + i)->getOccupant())->getColor() != color)) {
				authorizedMoves.push_back((x + i) * 8 + y + i);
				board->getCase((x + i), (y + i))->addThreat(this);
			}
			break;
		}
	}

	//Move top left
	for (int i = 1; (x + i < 8) && (y - i >= 0); i++) {
		if (!(board->getCase(x + i, y - i))->isOccupied()) {
			authorizedMoves.push_back((x + i) * 8 + (y - i));
			board->getCase((x + i), (y - i))->addThreat(this);
		}

		else {
			if (((board->getCase(x + i, y - i)->getOccupant())->getColor() != color)) {
				authorizedMoves.push_back((x + i) * 8 + (y - i));
				board->getCase((x + i), (y - i))->addThreat(this);
			}
			break;
		}
	}

	//Move back right
	for (int i = 1; (x - i >= 0) && (y + i < 8); i++) {
		if (!(board->getCase(x - i, y + i))->isOccupied()) {
			authorizedMoves.push_back((x - i) * 8 + (y + i));
			board->getCase((x - i), (y + i))->addThreat(this);
		}

		else {
			if (((board->getCase(x - i, y + i)->getOccupant())->getColor() != color)) {
				authorizedMoves.push_back((x - i) * 8 + (y + i));
				board->getCase((x - i), (y + i))->addThreat(this);
			}
			break;
		}
	}

	//Move back left
	for (int i = 1; (x - i >= 0) && (y - i >= 0); i++) {
		if (!(board->getCase(x - i, y - i))->isOccupied()) {
			authorizedMoves.push_back((x - i) * 8 + (y - i));
			board->getCase((x - i), (y - i))->addThreat(this);
		}

		else {
			if (((board->getCase(x - i, y - i)->getOccupant())->getColor() != color)) {
				authorizedMoves.push_back((x - i) * 8 + (y - i));
				board->getCase((x - i), (y - i))->addThreat(this);
			}
			break;
		}
	}


}