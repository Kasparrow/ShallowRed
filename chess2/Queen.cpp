#include "Piece.h"
#include "Board.h"

Queen::Queen() : Piece() {

}

Queen::Queen(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {

}

char Queen::getName() {
	if (color == 'b')
		return 'Q';
	else
		return 'q';
}

void Queen::calculateAuthorizedMoves() {
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
				board->getCase(x, y + i)->addThreat(this);
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