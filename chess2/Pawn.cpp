#include "Piece.h"
#include "Board.h"

using namespace std;

Pawn::Pawn() : Piece() {

}

Pawn::Pawn(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {

}

char Pawn::getName() {
	if (color == 'b')
		return 'P';
	else
		return 'p';
}

void Pawn::calculateAuthorizedMoves() {

	authorizedMoves.clear();

	//White Pawn :
	if (color == 'w') {
		//Move forward
		if (x + 1 < 8 && !(board->getCase(x + 1, y))->isOccupied()) {
			authorizedMoves.push_back((x + 1) * 8 + y);
			if (x == 1 && !(board->getCase(x + 2, y))->isOccupied())
				authorizedMoves.push_back((x + 2) * 8 + y);
		}

		//Take
		if ((x + 1 < 8 && y - 1 >= 0) && board->getCase(x + 1, y - 1)->isOccupied() && ((board->getCase(x + 1, y - 1))->getOccupant())->getColor() != 'w') {
			authorizedMoves.push_back((x + 1) * 8 + (y - 1));
			board->getCase((x + 1), (y - 1))->addThreat(this);
		}

		if ((x + 1 < 8 && y + 1 <8) && board->getCase(x + 1, y + 1)->isOccupied() && ((board->getCase(x + 1, y + 1))->getOccupant())->getColor() != 'w') {
			authorizedMoves.push_back((x + 1) * 8 + (y + 1));
			board->getCase((x + 1), (y + 1))->addThreat(this);
		}

		//TODO : En passant

	}


	//Black Pawn :
	if (color == 'b') {
		//Move forward
		if (x - 1 >= 0 && !(board->getCase(x - 1, y))->isOccupied()) {
			authorizedMoves.push_back((x - 1) * 8 + y);
			if (x == 6 && !(board->getCase(x - 2, y))->isOccupied())
				authorizedMoves.push_back((x - 2) * 8 + y);
		}

		//Take
		if ((x - 1 >= 0 && y - 1 >= 0) && board->getCase(x - 1, y - 1)->isOccupied() && ((board->getCase(x - 1, y - 1))->getOccupant())->getColor() != 'b') {
			authorizedMoves.push_back((x - 1) * 8 + (y - 1));
			board->getCase((x - 1), (y - 1))->addThreat(this);
		}

		if ((x - 1 >= 0 && y + 1 < 8) && board->getCase(x - 1, y + 1)->isOccupied() && ((board->getCase(x - 1, y + 1))->getOccupant())->getColor() != 'b') {
			authorizedMoves.push_back((x - 1) * 8 + (y + 1));
			board->getCase((x - 1), (y + 1))->addThreat(this);
		}

		//TODO : En passant
	}
} 